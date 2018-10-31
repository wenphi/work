#include "robotStateMechine/robotStateMechine.hpp"
#include "base/messageBase.hpp"
#include "base/messageType.hpp"
#include "base/stateBase.hpp"
#include <csignal>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <sys/time.h>

bool stopFlag = false;
moduleBase *robotStateMechine ::baseInstance = NULL;
std::string taddress = "ipc://stateMechine.ipc";
// std::string taddress = "tcp://192.168.1.81:5566";
/*
{
    msgType:
    module:
    msgData:{}
    needReply:
}
*/
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
    jsonCmd["needReply"] = true;
    return jsonCmd;
}
//motion--addline
void sendHook0()
{
    timeval tstart, tend;
    gettimeofday(&tstart, 0);
    messageClient *client0 = new messageClient(taddress, "Client0sendHook0");
    // messageClient *client0 = new messageClient(taddress);
    gettimeofday(&tend, 0);
    long start = ((long)tstart.tv_sec) * 1000 + (long)tstart.tv_usec / 1000;
    long end = ((long)tend.tv_sec) * 1000 + (long)tend.tv_usec / 1000;
    std::cout << "create client use time:" << end - start << " ms" << std::endl;

    int count = 0;
    //发送
    std::string msg = "hello,i'am Client0 sendHook0";
    Json::Value jsonReply;
    while (!stopFlag)
    {
        Json::Value jsonDate = encodeCmd(msgModule_t::MSG_MODULE_MOTION, 0, msg, count);
        // std::cout << jsonDate.toStyledString() << std::endl;
        if (client0->sendJson(jsonDate) < 0)
        {
            //快速收取
            std::cout << "clinet0 sendHook0 send message failed!" << std::endl;
            // while (1)
            // {
            //     jsonReply = client0->recvJson();
            //     if (!jsonReply.isNull())
            //         std::cout << "send hook0: recv: " << jsonReply["message"].asString() << std::endl;
            //     else
            //         break;
            // }
            continue;
        }

        std::cout << "send hook0: debug: send done! " << count << std::endl;

        jsonReply = client0->recvJson();
        if (!jsonReply.isNull())
        {
            std::cout << "send hook0: recv: " << jsonReply.toStyledString() << std::endl;
            // sleep(1);
            usleep(1);
        }
        else
        {
            std::cout << "send hook0: recv: NULL!"
                      << " "
                      << count << std::endl;
            usleep(1);
        }

        // }
        // usleep(10000); //延时10ms

        count++;
    }
    delete client0;
    std::cout << "apiThread0:"
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
    threads.emplace_back(sendHook0);
    // threads.emplace_back(sendHook1);
    // threads.emplace_back(sendHook2);
    while (!stopFlag)
    {
        sleep(1);
    }
    for (auto &thr : threads)
        thr.join();
    std::cout << "all thread exit done!" << std::endl;

    std::cout << "term exit done!" << std::endl;
    return 0;
}