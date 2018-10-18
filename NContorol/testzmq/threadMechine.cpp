#include "zhelpers.h"
#include <thread>
#include <vector>
#include <iostream>
#include <vector>
#include <string>
#include <csignal>
#include <jsoncpp/json/json.h>

using namespace std;
bool stopFlag = false;
string ipc_addr = "ipc://tmechine.ipc";

//中断处理函数
void stop(int sig)
{
    if (sig)
        stopFlag = true;
}
void apiThread(void *pCtx, int num)
{
    //创建socket
    void *pSock;
    pSock = zmq_socket(pCtx, ZMQ_DEALER);
    //设置发送超时
    int iSndTimeout = 5000; //单位ms
    zmq_setsockopt(pSock, ZMQ_SNDTIMEO, &iSndTimeout, sizeof(iSndTimeout));
    //设置id
    char cnum[0];
    sprintf(cnum, "%d", num);
    std::string threadId = "client." + std::string(cnum);
    zmq_setsockopt(pSock, ZMQ_IDENTITY, threadId.c_str(), threadId.size());
    //连接
    zmq_connect(pSock, ipc_addr.c_str());

    Json::Value jsonReply;
    Json::Reader reader;
    char *charReply;
    int count = 0;
    //发送的消息
    Json::Value jsonMsg;
    string msg = "from thread" + string(cnum);
    jsonMsg["cmd"] = num;
    jsonMsg["message"] = msg;
    while (!stopFlag)
    {
        //DEALER发送
        s_send(pSock, const_cast<char *>(jsonMsg.toStyledString().c_str()));
        //DEALER接收
        charReply = s_recv(pSock);

        reader.parse(charReply, jsonReply);
        cout << "thread: " << num
             << " recv:" << jsonReply["message"].asString()
             << " reply for thread:" << jsonReply["data"].asInt()
             << endl;
        free(charReply);
        sleep(1);
        count++;
    }
    zmq_close(pSock);
    cout << "apiThread" << num << "send num:" << count << " exit done!" << endl;
}

int main()
{
    vector<std::thread> threads;
    int count[10];
    signal(SIGINT, stop);
    for (int i = 0; i < 10; i++)
    {
        count[i] = 0;
    }
    //创建环境
    void *pCtx = zmq_ctx_new();
    //创建socket
    void *pSock = zmq_socket(pCtx, ZMQ_ROUTER);
    //设置接收超时时间
    int rcvTimeout = 5000;
    zmq_setsockopt(pSock, ZMQ_RCVTIMEO, &rcvTimeout, sizeof(rcvTimeout));
    //绑定
    zmq_bind(pSock, ipc_addr.c_str());
    //创建十个线程
    for (int i = 0; i < 10; i++)
    {
        threads.emplace_back(apiThread, pCtx, i);
    }
    Json::Reader reader;
    Json::Value jsonReply;
    int cmd;
    string message;
    Json::Value data;
    char *address;
    char *charRcv;

    cout << "main:start" << endl;
    while (!stopFlag)
    {
        //循环等待接收到来的消息，当超过5秒没有接到消息时，返回NULL
        //1.地址帧
        address = s_recv(pSock);
        if (address == NULL)
        {
            cout << "main:do something else..." << endl;
            sleep(1);
            continue;
        }
        //2.数据帧
        charRcv = s_recv(pSock);
        //处理消息
        reader.parse(charRcv, data);
        free(charRcv);
        cmd = data["cmd"].asInt();
        message = data["data"].asString();
        count[cmd]++;
        //应答消息
        jsonReply["message"] = "cmd done!";
        jsonReply["data"] = cmd;
        //router应答指定dealer
        s_sendmore(pSock, address);
        s_send(pSock, const_cast<char *>(jsonReply.toStyledString().c_str()));
        free(address);
    }
    //安全退出
    stopFlag = true;
    for (auto &thr : threads)
        thr.join();
    for (int i = 0; i < 10; i++)
    {
        cout << "get cmd:" << i << " num:"
             << count[i] << endl;
    }
    cout << "thread exit done!" << endl;
    zmq_close(pSock);
    zmq_ctx_destroy(pCtx);
    cout << "term exit done!" << endl;
    return 0;
}
