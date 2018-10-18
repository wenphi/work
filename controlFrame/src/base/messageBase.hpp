#pragma once
#include "zhelpers.h"
#include <jsoncpp/json/json.h>
#include <iostream>

//客户段可以选择一次发送接收多条
class messageClient
{
  public:
    messageClient(std::string address_, std::string id, int blockTime)
    {
        address = address_;
        clientid = id;
        idDealer = id + std::string(".dealer");
        idReq = id + std::string(".req");
        // std::cout << "debug:client:address:" << idDealer << "||" << idReq << std::endl;
        //创建环境
        context = zmq_ctx_new();
        //创建socket
        pSockDealer = zmq_socket(context, ZMQ_DEALER);
        pSockReq = zmq_socket(context, ZMQ_REQ);
        //设置阻塞时间
        zmq_setsockopt(pSockDealer, ZMQ_SNDTIMEO, &blockTime, sizeof(blockTime));
        zmq_setsockopt(pSockDealer, ZMQ_RCVTIMEO, &blockTime, sizeof(blockTime));
        //设置退出时的等待时间--1000ms
        int linger_time = 1000;
        zmq_setsockopt(pSockDealer, ZMQ_LINGER, &linger_time, sizeof(linger_time));
        zmq_setsockopt(pSockReq, ZMQ_LINGER, &linger_time, sizeof(linger_time));
        //设置id
        zmq_setsockopt(pSockDealer, ZMQ_IDENTITY, idDealer.c_str(), idDealer.size());
        zmq_setsockopt(pSockReq, ZMQ_IDENTITY, idReq.c_str(), idReq.size());
        //连接
        zmq_connect(pSockDealer, address.c_str());
        zmq_connect(pSockReq, address.c_str());
        //完成
        msgReady = true;
    };
    messageClient(std::string address_)
    {
        char identity[10];
        sprintf(identity, "%04X-%04X", within(0x10000), within(0x10000));
        clientid = std::string(identity);
        idDealer = std::string(identity) + std::string(".dealer");
        idReq = std::string(identity) + std::string(".req");
        address = address_;
        //创建环境
        context = zmq_ctx_new();
        //创建socket
        pSockDealer = zmq_socket(context, ZMQ_DEALER);
        pSockReq = zmq_socket(context, ZMQ_REQ);
        //配置id
        zmq_setsockopt(pSockDealer, ZMQ_IDENTITY, &idDealer, sizeof(idDealer));
        zmq_setsockopt(pSockReq, ZMQ_IDENTITY, &idReq, sizeof(idReq));
        //设置socket退出时的阻塞时间--1000ms
        int linger_time = 1000;
        zmq_setsockopt(pSockDealer, ZMQ_LINGER, &linger_time, sizeof(linger_time));
        zmq_setsockopt(pSockReq, ZMQ_LINGER, &linger_time, sizeof(linger_time));
        //连接
        zmq_connect(pSockDealer, address.c_str());
        zmq_connect(pSockReq, address.c_str());
        //完成
        msgReady = true;
    };
    ~messageClient()
    {
        zmq_close(pSockDealer);
        zmq_close(pSockReq);
        zmq_ctx_destroy(context);
        std::cout << "client:" << clientid << " exit done!" << std::endl;
    };
    //初始化

    //发送json格式的消息
    int sendJson(Json::Value &jsonData)
    {
        return s_send(pSockDealer, const_cast<char *>(jsonData.toStyledString().c_str()));
    };
    int sendJson_block(Json::Value &JsonData)
    {
        return s_send(pSockReq, const_cast<char *>(JsonData.toStyledString().c_str()));
    };
    //发送char格式的消息
    int sendChar(char *charData, int len)
    {
        return zmq_send(pSockDealer, charData, len, 0);
    };
    int sendChar_block(char *charData, int len)
    {
        return zmq_send(pSockReq, charData, len, 0);
    }
    //接收json格式的消息
    Json::Value recvJson()
    {
        Json::Reader reader;
        Json::Value jsonData;
        if (!msgReady)
            return jsonData;
        char *charData = s_recv(pSockDealer);
        if (charData == NULL)
            return jsonData;
        reader.parse(charData, jsonData);
        free(charData);
        return jsonData;
    };
    Json::Value recvJson_block()
    {
        Json::Reader reader;
        Json::Value jsonData;
        if (!msgReady)
            return jsonData;
        char *charData = s_recv(pSockReq);
        if (charData == NULL)
            return jsonData;
        reader.parse(charData, jsonData);
        free(charData);
        return jsonData;
    };
    //接收char*格式的消息,消息使用后记得释放!!
    char *recvChar()
    {
        return s_recv(pSockDealer);
    };
    char *recvChar_block()
    {
        return s_recv(pSockReq);
    }

  private:
    bool msgReady = false;

    std::string clientid;
    std::string idDealer; //zmq的sock标识
    std::string idReq;
    std::string address; //zmq链接的通讯地址

    void *context;     //zmq的环境/上下文
    void *pSockDealer; //zmq创建Dealer的sock
    void *pSockReq;    //zmq创建Req的sock
    int blockTime;     //阻塞时间
};

//一次只允许执行一条命令,否则导致发送地址出错
class messageServer
{
  public:
    messageServer(std::string address_)
    {
        address = address_;
        //发送--接收阻塞时间/ms
        rblockTime = 1000;
        sblockTime = 1000;
        //创建环境
        context = zmq_ctx_new();
        //创建socket
        pSockRouter = zmq_socket(context, ZMQ_ROUTER);
        //设置阻塞时间
        zmq_setsockopt(pSockRouter, ZMQ_SNDTIMEO, &sblockTime, sizeof(sblockTime));
        zmq_setsockopt(pSockRouter, ZMQ_RCVTIMEO, &rblockTime, sizeof(rblockTime));
        //设置socket退出时的阻塞时间--1000ms
        int linger_time = 1000;
        zmq_setsockopt(pSockRouter, ZMQ_LINGER, &linger_time, sizeof(linger_time));
        //绑定
        zmq_bind(pSockRouter, address.c_str());
        //完成
        msgReady = true;
    };
    ~messageServer()
    {
        zmq_close(pSockRouter);
        zmq_ctx_destroy(context);
        std::cout << "server:"
                  << "exit done!" << std::endl;
    };
    //初始化

    //发送
    int sendJson(Json::Value &jsonData)
    {
        int ret1, ret2, ret3;
        ret1 = s_sendmore(pSockRouter, const_cast<char *>(address.c_str()));
        if (ret1 < 0)
            return ret1;

        if (isBlock)
        {
            ret2 = s_sendmore(pSockRouter, (char *)"");
            if (ret2 < 0)
                return ret2;
        }
        ret3 = s_send(pSockRouter, const_cast<char *>(jsonData.toStyledString().c_str()));
        return ret3;
    };
    int sendChar(char *charData, int len)
    {
        int ret1, ret2, ret3;
        ret1 = s_sendmore(pSockRouter, const_cast<char *>(address.c_str()));
        if (ret1 < 0)
            return ret1;

        if (isBlock)
        {
            ret2 = s_sendmore(pSockRouter, (char *)"");
            if (ret2 < 0)
                return ret2;
        }
        ret3 = zmq_send(pSockRouter, charData, len, 0);
        return ret3;
    };
    //接收
    Json::Value recvJson()
    {
        Json::Reader reader;
        Json::Value jsonData;
        if (!msgReady)
            return jsonData;
        char *msgAddr = s_recv(pSockRouter);
        if (msgAddr == NULL)
            return jsonData;
        address = std::string(msgAddr); //保存地址
        free(msgAddr);
        char *charData = s_recv(pSockRouter);
        if (strcmp(charData, "") == 0)
        {
            isBlock = true;
            free(charData);
            charData = s_recv(pSockRouter);
        }
        else
            isBlock = false;
        reader.parse(charData, jsonData);
        free(charData);
        return jsonData;
    };
    //错误返回空指针,消息使用后记得释放!!
    char *recvChar()
    {
        char *charData = NULL;
        if (!msgReady)
            return charData;
        char *msgAddr = s_recv(pSockRouter);
        if (msgAddr == NULL)
            return charData;
        address = std::string(msgAddr); //保存地址
        free(msgAddr);
        charData = s_recv(pSockRouter);
        if (strcmp(charData, "") == 0)
        {
            isBlock = true;
            free(charData);
            charData = s_recv(pSockRouter);
        }
        else
            isBlock = false;
        return charData;
    };

  private:
    bool msgReady = false;
    bool isBlock; //每次调用recv后刷新,决定了发送类型{地址+""+数据}/{地址+数据}

    std::string clientid; //每次调用recv后刷新,决定了下一次send的发送地址;

    std::string address; //zmq链接的通讯地址

    void *context;     //zmq的环境/上下文
    void *pSockRouter; //zmq创建Router的sock

    int rblockTime; //接收阻塞时间
    int sblockTime; //发送阻塞时间
};