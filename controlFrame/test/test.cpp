#include "../src/robotStateMechine/robotStateMechine.hpp"
#include <zmq.h>
#include <csignal>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

bool stopFlag = false;
moduleBase *robotStateMechine ::baseInstance = NULL;

char *encodeCmd(int module, int cmd, std::string message)
{
    Json::Value jsonCmd;
    Json::Value root;
    root["data"] = 123456;
    jsonCmd["module"] = module;
    jsonCmd["cmd"] = cmd;
    root["message"] = message;
    jsonCmd["params"] = root;
    std::string result = jsonCmd.toStyledString();
    return const_cast<char *>(result.c_str());
}
int s_send(void *socket, char *string)
{
    int rc;
    zmq_msg_t message;
    zmq_msg_init_size(&message, strlen(string));
    memcpy(zmq_msg_data(&message), string, strlen(string));
    rc = zmq_sendmsg(socket, &message, 0);
    zmq_msg_close(&message);
    return (rc);
}
void sendHook(void *pctx)
{
    if (pctx == NULL)
    {
        std::cout << "the ctx is NULL!" << std::endl;
        return;
    }
    void *pCtx = pctx;
    //创建socket
    void *pSock;
    if ((pSock = zmq_socket(pCtx, ZMQ_DEALER)) == NULL)
    {
        return;
    }
    int iSndTimeout = 10; // millsecond
    //设置接收超时
    if (zmq_setsockopt(pSock, ZMQ_RCVTIMEO, &iSndTimeout, sizeof(iSndTimeout)) < 0)
    {
        zmq_close(pSock);
        return;
    }
    //连接目标IP192.168.1.2，端口7766
    if (zmq_connect(pSock, "ipc://stateMechine.ipc") < 0)
    {
        zmq_close(pSock);
        return;
    }
    char *data;
    int count = 0;
    std::string msg = "hello";
    while (!stopFlag)
    {
        data = encodeCmd(0, 0, msg);
        if (s_send(pSock, data) < 0)
        {
            std::cout << "can't send message in thread:" << std::endl;
            usleep(100);
            continue;
        }
        // std::cout << data << std::endl;
        usleep(10000);
        count++;
    }
    zmq_close(pSock);
    std::cout << "apiThread"
              << "send num:" << count << " exit done!" << std::endl;
}

void stop(int sig)
{
    if (sig)
        stopFlag = true;
}

int main()
{
    signal(SIGINT, stop);
    robotStateMechine *rsm = new robotStateMechine();
    void *pCtx = zmq_ctx_new();
    rsm->getContext(pCtx);
    std::thread t1(sendHook, pCtx);
    std::thread t2(&robotStateMechine::updateHook, rsm);
    rsm->setStart();
    while (!stopFlag)
    {
        sleep(1);
    }
    rsm->setStop();
    t1.join();
    t2.join();
    zmq_ctx_destroy(pCtx);
    return 0;
}