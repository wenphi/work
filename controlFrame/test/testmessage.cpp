#include <csignal>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include "base/messageBase.hpp"

std::string addr = "ipc://testMsg.ipc";
bool stopFlag = false;

void stop(int sig)
{
    if (sig)
        stopFlag = true;
}
void apiThread(int num)
{
    char cmd[0];
    sprintf(cmd, "%d", num);
    std::string clientName = "client." + std::string(cmd);
    messageClient *client = new messageClient(addr, clientName, 5000);

    std::string msg = "hello i'm client:" + std::string(cmd);
    Json::Value jsonMsg;
    Json::Value jsonReply;
    jsonMsg["cmd"] = num;
    Json::Reader reader;
    jsonMsg["message"] = msg;
    int count = 0;
    sleep(1);
    while (!stopFlag)
    {
        client->sendJson(jsonMsg);

        jsonReply = client->recvJson();
        std::cout << "thread: " << num
                  << " recv:" << jsonReply["message"].asString()
                  << " for thread:" << jsonReply["data"].asInt()
                  << std::endl;
        // cout << data << endl;
        sleep(1);
        count++;
    }
    std::cout << "apiThread" << num << "send num:" << count << " exit done!" << std::endl;
    delete client;
}
void apiThreadBlock(int num)
{
    char cmd[0];
    sprintf(cmd, "%d", num);
    std::string clientName = "client." + std::string(cmd);
    messageClient *client = new messageClient(addr, clientName, 5000);

    std::string msg = "hello i'm client:" + std::string(cmd);
    Json::Value jsonMsg;
    Json::Value jsonReply;
    jsonMsg["cmd"] = num;
    Json::Reader reader;
    jsonMsg["message"] = msg;
    int count = 0;
    sleep(1);
    while (!stopFlag)
    {
        client->sendJson_block(jsonMsg);

        jsonReply = client->recvJson_block();
        std::cout << "thread: " << num
                  << " recv:" << jsonReply["message"].asString()
                  << " for thread:" << jsonReply["data"].asInt()
                  << std::endl;
        // cout << data << endl;
        // sleep(5);
        count++;
    }
    std::cout << "apiThreadBlock" << num << "send num:" << count << " exit done!" << std::endl;
    delete client;
}

int main()
{
    std::vector<std::thread> threads;
    int countExit = 0;
    int count[10];
    signal(SIGINT, stop);
    for (int i = 0; i < 10; i++)
    {
        count[i] = 0;
    }
    //上下文
    messageServer *server = new messageServer(addr);
    //创建十个子线程
    for (int i = 0; i < 5; i++)
    {
        threads.emplace_back(apiThread, i);
    }
    for (int i = 5; i < 10; i++)
    {
        threads.emplace_back(apiThreadBlock, i);
    }
    Json::Value jsonReply;
    int cmd;
    std::string message;
    Json::Value jsonData;
    char *address;
    char *charRcv;
    std::cout << "main:start" << std::endl;
    // sleep(1);
    // while (!stopFlag)
    while (1)
    {
        //循环等待接收到来的消息，当超过5秒没有接到消息时，
        jsonData = server->recvJson();
        if (jsonData.isNull())
        {
            std::cout << "do something else..." << std::endl;
            countExit++;
            if (countExit > 5)
                break;
            continue;
        }

        cmd = jsonData["cmd"].asInt();
        message = jsonData["data"].asString();
        switch (cmd)
        {
        case 0:
            count[0]++;
            usleep(1);
            break;
        case 1:
            count[1]++;
            usleep(2000);
            break;
        case 2:
            count[2]++;
            // usleep(3000);
            break;
        case 3:
            count[3]++;
            // usleep(4000);
            break;
        case 4:
            count[4]++;
            // usleep(5000);
            break;
        case 5:
            count[5]++;
            // usleep(6000);
            break;
        case 6:
            count[6]++;
            // usleep(7000);
            break;
        case 7:
            count[7]++;
            // usleep(8000);
            break;
        case 8:
            count[8]++;
            // usleep(9000);
            break;
        case 9:
            count[9]++;
            // usleep(10000);
            break;
        }
        jsonReply["message"] = "cmd done!";
        jsonReply["data"] = cmd;
        server->sendJson(jsonReply);
        countExit = 0;
        // usleep(1);
    }
    //安全退出
    stopFlag = true;
    for (auto &thr : threads)
        thr.join();
    for (int i = 0; i < 10; i++)
    {
        std::cout << "get cmd:" << i << " num:"
                  << count[i] << std::endl;
    }
    std::cout << "thread exit done!" << std::endl;
    delete server;
    return 0;
}