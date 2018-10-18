#include "../src/robotStateMechine/robotStateMechine.hpp"
#include "base/messageBase.hpp"
#include <zmq.h>
#include <csignal>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

bool stopFlag = false;
moduleBase *robotStateMechine ::baseInstance = NULL;
std::string taddress = "ipc://stateMechine.ipc";

Json::Value encodeCmd(int module, int cmd, std::string message, int data = 123456)
{
    Json::Value jsonCmd;
    Json::Value root;
    root["data"] = data;
    jsonCmd["module"] = module;
    jsonCmd["cmd"] = cmd;
    root["message"] = message;
    jsonCmd["params"] = root;
    return jsonCmd;
}
//motion--addline
void sendHook0()
{
    messageClient *client0 = new messageClient(taddress, "sendHook0", 1000);
    int count = 0;
    //发送
    std::string msg = "hello,i'am sendHook0";
    Json::Value jsonDate = encodeCmd(0, 0, msg);
    Json::Value jsonReply;
    while (!stopFlag)
    {
        client0->sendJson(jsonDate);
        jsonReply = client0->recvJson();
        if (!jsonReply.isNull())
            std::cout << "send hook0: recv: " << jsonReply["message"].asString() << std::endl;
        // usleep(1000000);
        count++;
    }
    delete client0;
    std::cout << "apiThread0:"
              << "send num:" << count << " exit done!" << std::endl;
}
//motion--queryTemperature
void sendHook1()
{
    messageClient *client0 = new messageClient(taddress, "sendHook1", 1000);
    int count = 0;
    //发送
    std::string msg = "hello,i'am sendHook1";
    Json::Value jsonDate = encodeCmd(0, 1, msg);
    Json::Value jsonReply;
    while (!stopFlag)
    {
        client0->sendJson(jsonDate);
        jsonReply = client0->recvJson();
        if (!jsonReply.isNull())
            std::cout << "send hook1: recv: " << jsonReply["message"].asString() << std::endl;
        // usleep(1000000);
        count++;
    }
    delete client0;
    std::cout << "apiThread1:"
              << "send num:" << count << " exit done!" << std::endl;
}
//io--setDibit
void sendHook2()
{
    messageClient *client0 = new messageClient(taddress, "sendHook2", 1000);
    int count = 0;
    //发送
    std::string msg = "hello,i'am sendHook2";
    Json::Value jsonDate;
    Json::Value jsonReply;
    int flag;
    while (!stopFlag)
    {
        flag = count % 2;
        jsonDate = encodeCmd(1, 1, msg, flag);
        client0->sendJson(jsonDate);
        jsonReply = client0->recvJson();
        if (!jsonReply.isNull())
            std::cout << "send hook2: recv: " << jsonReply["message"].asString() << std::endl;
        // usleep(1000000);
        count++;
    }
    delete client0;
    std::cout << "apiThread2:"
              << "send num:" << count << " exit done!" << std::endl;
}
void stop(int sig)
{
    if (sig)
        stopFlag = true;
}

int main()
{
    std::vector<std::thread> threads;
    signal(SIGINT, stop);
    robotStateMechine *rsm = new robotStateMechine(taddress);
    threads.emplace_back(&robotStateMechine::updateHook, rsm);
    threads.emplace_back(sendHook0);
    threads.emplace_back(sendHook1);
    threads.emplace_back(sendHook2);

    rsm->setStart();
    while (!stopFlag)
    {
        sleep(1);
    }
    rsm->setStop();
    for (auto &thr : threads)
        thr.join();
    std::cout << "all thread exit done!" << std::endl;

    delete rsm;
    std::cout << "term exit done!" << std::endl;
    return 0;
}