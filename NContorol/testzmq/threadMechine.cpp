//测试在多个子线程下的收发情况
#include "mechine.hpp"
#include <thread>
#include <vector>
// #include <stdint.h>

using namespace std;
bool stopFlag = false;

void stop(int sig)
{
    if (sig)
        stopFlag = true;
}

void apiThread(void *ctx, int num)
{
    if (ctx == NULL)
    {
        cout << "the ctx is NULL!" << endl;
        return;
    }
    void *pCtx = ctx;
    //创建socket
    void *pSock;
    if ((pSock = zmq_socket(pCtx, ZMQ_DEALER)) == NULL)
    {
        zmq_ctx_destroy(pCtx);
        return;
    }
    int iSndTimeout = 5000; // millsecond
    //设置接收超时
    if (zmq_setsockopt(pSock, ZMQ_SNDTIMEO, &iSndTimeout, sizeof(iSndTimeout)) < 0)
    {
        zmq_close(pSock);
        zmq_ctx_destroy(pCtx);
        return;
    }
    //连接目标IP192.168.1.2，端口7766
    if (zmq_connect(pSock, "ipc://tmechine.ipc") < 0)
    {
        zmq_close(pSock);
        zmq_ctx_destroy(pCtx);
        return;
    }
    int i;
    string cmd = getString(num);
    string msg = "from thread" + cmd;
    Json::Value jsonMsg;
    Json::Value jsonReply;
    jsonMsg["cmd"] = num;
    jsonMsg["message"] = msg;
    int count = 0;
    while (!stopFlag)
    {
        if (s_send(pSock, jsonMsg) < 0)
        {
            cout << "can't send message in thread:" << num << endl;
            usleep(1000);
            continue;
        }
        if (!s_recv(pSock, jsonReply))
        {
            cout << "thread recv out time!" << endl;
            usleep(100);
            continue;
        }
        cout << "thread: " << num
             << " recv:" << jsonReply["message"].asString()
             << " for thread:" << jsonReply["data"].asInt()
             << endl;
        // cout << data << endl;
        // usleep(10000);
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
    //上下文
    void *pCtx = zmq_ctx_new();
    if (pCtx == NULL)
    {
        cout << "create ctx failed!" << endl;
        return 0;
    }
    //创建套接字
    // void *pSock = zmq_socket(pCtx, ZMQ_DEALER);
    void *pSock = zmq_socket(pCtx, ZMQ_ROUTER);
    //设置超时时间
    int rcvTimeout = 500;
    zmq_setsockopt(pSock, ZMQ_RCVTIMEO, &rcvTimeout, sizeof(rcvTimeout));
    zmq_setsockopt(pSock, ZMQ_SNDTIMEO, &rcvTimeout, sizeof(rcvTimeout));
    zmq_bind(pSock, "ipc://tmechine.ipc");
    //创建十个子线程
    for (int i = 0; i < 10; i++)
    {
        threads.emplace_back(apiThread, pCtx, i);
    }
    Json::Value jsonCmd;
    Json::Value jsonReply;
    int cmd;
    string identifine;
    string message;
    Json::Value data;
    while (!stopFlag)
        while (1)
        {
            //循环等待接收到来的消息，当超过5秒没有接到消息时，
            if (!s_recvMore(pSock, identifine))
            {
                cout << "server recvmore data out time!" << endl;
                break;
            }
            if (!s_recv(pSock, data))
            {
                cout << "server recv data out time!" << endl;
                break;
            }
            cmd = data["cmd"].asInt();
            message = data["data"].asString();
            if (stopFlag)
                cout << "cmd:" << cmd << endl;
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
            if (s_send(pSock, jsonReply) < 0)
            {
                cout << "main send data out time !" << endl;
            }
            // usleep(2);
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
    cout << "exit add done!" << endl;
    return 0;
}

// void mechineState()
// {
// }
