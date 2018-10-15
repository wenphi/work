#include <zmq.h>
#include <jsoncpp/json/json.h>
#include <iostream>
#include <thread>
#include "mechine.hpp"

void apithread(void *pctx)
{
    void *psock = zmq_socket(pctx, ZMQ_DEALER);
    zmq_connect(psock, "ipc://pubsubMsg.ipc");
    std::string id = "thread0";
    zmq_setsockopt(psock, ZMQ_IDENTITY, &id, sizeof(id));
    int rcvTimeout = 1000;
    zmq_setsockopt(psock, ZMQ_RCVTIMEO, &rcvTimeout, sizeof(rcvTimeout));
    Json::Value jsonMsg;
    Json::Value jsonReply;
    std::string msg;
    jsonMsg["message"] = "hello main()!";
    while (1)
    {
        // s_recvMore(psock, msg);
        // s_recv(psock, jsonMsg);
        s_sendMore(psock, id);
        s_send(psock, jsonMsg);
        // usleep(10);
        s_recv(psock, jsonReply);
        std::cout << "thread :" << jsonReply["message"].asString() << std::endl;
    }
}

int main()
{
    void *pctx = zmq_ctx_new();
    void *psock = zmq_socket(pctx, ZMQ_ROUTER);
    zmq_bind(psock, "ipc://pubsubMsg.ipc");
    // int rcvOuttime = 50000;
    // zmq_setsockopt(psock, ZMQ_RCVTIMEO, &rcvOuttime, sizeof(rcvOuttime));
    std::string address;
    Json::Value jsonMsg;
    Json::Value jsonReply;
    std::thread t1(apithread, pctx);
    sleep(1);
    while (1)
    {
        if (!s_recvDealer(psock, address, jsonMsg))
        {
            std::cout << " main() rcv data out time !" << std::endl;
            sleep(1);
            continue;
        }
        std::cout << "msg address:" << address
                  << "data: " << jsonMsg["message"]
                  << std::endl;
        address = std::string("thread0");
        jsonReply["message"] = "cmd done!";
        s_sendMore(psock, address);
        s_send(psock, jsonReply);
        sleep(1);
    }
}

// void TestRouter_Req(void *context, void *router, char *link)
// {
//     void *identified0 = zmq_socket(context, ZMQ_REQ);
//     zmq_setsockopt(identified0, ZMQ_IDENTITY, "A0", 2);
//     zmq_connect(identified0, link);
//     s_send(identified0, "ROUTER-REQ");
//     // zmq_send(identified0, "ROUTER-REQ", 10, 0);
//     char *address = s_recv(router);
//     char *empty = s_recv(router);
//     free(empty);
//     char *content = s_recv(router);
//     printf("Router端收到来自：[%s]的数据： [%s] ", address, content);
//     free(content);
//     // Router发送回复信息
//     s_sendmore(router, address);
//     s_sendmore(router, "");
//     s_send(router, "Server Reply");

//     char *reqRec = s_recv(identified0);
//     printf("Req端收到数据:[%s]", reqRec);
//     free(reqRec);
//     free(address);
//     zmq_close(identified0);
// }

// //Router_Dealer之间的通讯演示
// void TestRouter_Dealer(void *context, void *router, char *link)
// {
//     void *identified1 = zmq_socket(context, ZMQ_DEALER);
//     zmq_setsockopt(identified1, ZMQ_IDENTITY, "A1", 2);
//     zmq_connect(identified1, link);
//     s_send(identified1, "ROUTER-DEALER");
//     char *address = s_recv(router);
//     char *content = s_recv(router);
//     printf("Router端收到来自：[%s]的数据：[%s] ", address, content);
//     free(content);
//     s_sendmore(router, address);
//     s_send(router, "Server Reply");

//     char *reqRec = s_recv(identified1);
//     printf("DEALER端收到数据:[%s]", reqRec);
//     free(reqRec);
//     zmq_close(identified1);
// }

// //Router_Rep之间的通讯演示
// void TestRouter_Rep(void *context, void *router, char *link)
// {
//     void *identified2 = zmq_socket(context, ZMQ_REP);
//     zmq_setsockopt(identified2, ZMQ_IDENTITY, "A2", 2);
//     zmq_connect(identified2, link);
//     usleep(500);
//     //rep必须先收到数据才能响应
//     s_sendmore(router, "A2");
//     s_sendmore(router, "");
//     s_send(router, "Router Send");
//     char *rec = s_recv(identified2);
//     printf("rep 端收到数据[%s]", rec);
//     free(rec);

//     // rep 回复
//     s_send(identified2, "Rep Reply");

//     //router 接收
//     char *address = s_recv(router);
//     char *empty = s_recv(router);
//     free(empty);
//     char *content = s_recv(router);

//     printf("Router端收到来自：[%s]的数据： [%s] ", address, content);
//     free(content);
//     free(address);
//     zmq_close(identified2);
// }

// //Router_Router之间的通讯演示
// void TestRouter_Router(void *context, void *router, char *link)
// {
//     void *identified3 = zmq_socket(context, ZMQ_ROUTER);
//     zmq_setsockopt(identified3, ZMQ_IDENTITY, "A3", 2);
//     zmq_connect(identified3, link);
//     usleep(500);
//     s_sendmore(identified3, "Server");
//     s_send(identified3, "ROUTER-ROUTER");
//     char *address = s_recv(router);
//     char *content = s_recv(router);

//     printf("Router监听端收到来自[%s]的数据：[%s] ", address, content);
//     free(address);
//     free(content);

//     s_sendmore(router, "A3");
//     s_send(router, "Server Reply");

//     address = s_recv(identified3);
//     content = s_recv(identified3);

//     printf("Router连接端收到来自[%s]的数据：[%s] ", address, content);
//     free(address);
//     free(content);

//     zmq_close(identified3);
// }
// void RouterUse()
// {
//     void *context = zmq_ctx_new();
//     char *link = "tcp://127.0.0.1:5005";
//     void *router = zmq_socket(context, ZMQ_ROUTER);
//     int iRet = -1;
//     //指定Server的名称
//     zmq_setsockopt(router, ZMQ_IDENTITY, "Server", 6);
//     zmq_bind(router, link);
//     printf("开始Router_Req之间的通讯演示");
//     TestRouter_Req(context, router, link);
//     printf("\n");
//     printf("开始Router_Dealer之间的通讯演示");
//     TestRouter_Dealer(context, router, link);
//     printf("\n");
//     printf("开始Router_Rep之间的通讯演示");
//     TestRouter_Rep(context, router, link);
//     printf("\n");
//     printf("开始Router_Router之间的通讯演示");
//     TestRouter_Router(context, router, link);

//     zmq_close(router);
//     zmq_ctx_destroy(context);
//     return;
// }

// int main()
// {
//     RouterUse();
//     getchar();
//     return 0;
// }