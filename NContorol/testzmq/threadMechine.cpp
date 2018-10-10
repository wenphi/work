//测试在多个子线程下的收发情况
#include "mechine.hpp"
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
    if (zmq_setsockopt(pSock, ZMQ_RCVTIMEO, &iSndTimeout, sizeof(iSndTimeout)) < 0)
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
    char *data;
    int count = 0;
    while (!stopFlag)
    {
        data = encodeCommand(num, msg);
        if (s_send(pSock, data) < 0)
        {
            cout << "can't send message in thread:" << num << endl;
            usleep(100);
            continue;
        }
        cout << data << endl;
        // usleep(10);
        count++;
    }
    zmq_close(pSock);
    cout << "apiThread" << num << "send num:" << count << " exit done!" << endl;
}
int main()
{
    vector<thread> threads;
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
    void *pSock = zmq_socket(pCtx, ZMQ_DEALER);
    // void *pPub = zmq_socket(pCtx, ZMQ_PUB);
    if (pSock == NULL)
    {
        cout << "create sock failed!" << endl;
        zmq_ctx_destroy(pCtx);
        return 0;
    }
    //设置超时时间
    int rcvTimeout = 5000;
    if (zmq_setsockopt(pSock, ZMQ_RCVTIMEO, &rcvTimeout, sizeof(rcvTimeout)))
    {
        cout << "set timeout error!" << endl;
        zmq_close(pSock);
        zmq_ctx_destroy(pCtx);
        return 0;
    }
    const char *paddr = "ipc://tmechine.ipc";
    // if (zmq_bind(pPub, "ipc://pubMessage.ipc") < 0)
    // {
    //     cout << "bind address error!" << endl;
    //     zmq_close(pSock);
    //     zmq_close(pPub);
    //     zmq_ctx_destroy(pCtx);
    //     return 0;
    // }
    if (zmq_bind(pSock, paddr) < 0)
    {
        cout << "bind address error!" << endl;
        zmq_close(pSock);
        // zmq_close(pPub);
        zmq_ctx_destroy(pCtx);
        return 0;
    }
    //创建十个子线程
    for (int i = 0; i < 10; i++)
    {
        threads.emplace_back(apiThread, pCtx, i);
    }
    Json::Value jsonCmd;
    int cmd;
    string message;
    // while (!stopFlag)
    while (1)
    {
        //循环等待接收到来的消息，当超过5秒没有接到消息时，
        char *data = s_recv(pSock);
        if (strcmp(data, " ") == 0)
            break;
        // cout << "rcv message: " << data << endl;
        jsonCmd = decodeCommand(data);
        cmd = jsonCmd["cmd"].asInt();
        message = jsonCmd["data"].asString();
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
    return 0;
}

// void mechineState()
// {
// }
