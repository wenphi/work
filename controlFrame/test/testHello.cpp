#include "../src/robotStateMechine/robotStateMechine.hpp"
#include "base/messageBase.hpp"
#include "base/messageType.hpp"
#include <zmq.h>
#include <csignal>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/time.h>

bool stopFlag = false;
// moduleBase *robotStateMechine ::baseInstance = NULL;
std::string taddress = "ipc:///home/ywh/stateMechine.ipc";

Json::Value encodeCmd(int module, int cmd, std::string message, int data = 123456)
{
    Json::Value jsonCmd;
    Json::Value root1;
    Json::Value root2;
    jsonCmd["msgType"] = msgtype_t::MSG_CMD;
    jsonCmd["module"] = module;
    root1["cmd"] = cmd;
    root2["param1"] = data;
    root2["param2"] = message;
    root2["param3"] = "sdj";
    root1["params"] = root2;
    jsonCmd["msgData"] = root1;
    jsonCmd["needReply"] = false;
    return jsonCmd;
}
void sendHook0()
{
    //创建客户端实例,
    messageClient *client0 = new messageClient(taddress, "clinethello", 1000);
    //消息内容
    int count = 0;
    std::string msg = "I'am Client Hello";
    Json::Value jsonReply;
    //循环发送
    while (!stopFlag)
    {
        //封装为指定json格式的消息
        Json::Value jsonData = encodeCmd(msgModule_t::MSG_MODULE_HELLO, 0, msg, count);
        //调用发送函数发送
        if (client0->sendJson(jsonData) < 0)
        {
            std::cout << "clientHello: the server is bussy now!" << std::endl;
            continue;
        }
        //调用接受函数接收
        jsonReply = client0->recvJson();
        if (!jsonReply.isNull())
            std::cout << "send hook0: recv: " << jsonReply["moduleReply"]["message"].asString() << std::endl;
        usleep(10000); //延时10ms
        count++;
    }
    delete client0;
    std::cout << "clientHello: send num" << count << " exit done!" << std::endl;
}
void sendHook1()
{
    //创建客户端实例,
    messageClient *client0 = new messageClient(taddress, "clinethello", 1000);
    //消息内容
    int count = 0;
    std::string msg = "I'am Client Hello";
    Json::Value jsonReply;
    //循环发送
    while (!stopFlag)
    {
        //封装为指定json格式的消息
        Json::Value jsonData = encodeCmd(msgModule_t::MSG_MODULE_HELLO, 0, msg, count);
        //调用发送函数发送
        if (client0->sendJson(jsonData) < 0)
        {
            std::cout << "clientHello: the server is bussy now!" << std::endl;
            continue;
        }
        //调用接受函数接收
        jsonReply = client0->recvJson();
        if (!jsonReply.isNull())
            std::cout << "send hook0: recv: " << jsonReply["moduleReply"]["message"].asString() << std::endl;
        usleep(10000); //延时10ms
        count++;
    }
    delete client0;
    std::cout << "clientHello: send num" << count << " exit done!" << std::endl;
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
    threads.emplace_back(sendHook0);
    while (!stopFlag)
    {
        sleep(1);
    }
    for (auto &thr : threads)
        thr.join();
    std::cout << "All thread exit done!" << std::endl;

    std::cout << "Terminal exit done!" << std::endl;
    return 0;
}