#include "robotStateMechine.hpp"
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <zmq.h>

bool robotStateMechine::recvMsg(void *sock, Json::Value &jsonMsg)
{
    Json::Reader reader;
    zmq_msg_t message;
    zmq_msg_init(&message);
    if (zmq_recvmsg(sock, &message, 0) < 0)
    {
        // std::cout << "wait out time" << std::endl;
        return false;
    }
    int size = zmq_msg_size(&message);
    char *string = (char *)malloc(size + 1);
    memcpy(string, zmq_msg_data(&message), size);
    zmq_msg_close(&message);
    string[size] = 0;
    std::cout << "recv: " << string << std::endl;
    if (reader.parse(string, jsonMsg))
        return true;
    else
        return false;
}

moduleBase *robotStateMechine::getModuleBasePtr()
{
    return baseInstance;
};
moduleBase *robotStateMechine::praseCmdtoModule(Json::Value &msg)
{
    //根据参数进行选取子类
    //指向子类
    switch (msg["module"].asInt())
    {
    case 0:
        baseInstance = &motionInstance;
        baseInstance->getMessage(msg);
        break;
    default:
        baseInstance = nullptr;
    }
    //baseInstance =&ioInstance;
    return baseInstance;
}

void robotStateMechine::updateHook()
{
    while (!stopFlag)
    {
        void *pSock = zmq_socket(pCtx, ZMQ_DEALER);
        if (pSock == NULL)
        {
            std::cout << "create state sock failed" << std::endl;
            std::cout << "exit updateHook!" << std::endl;
            return;
        }
        int rcvTimeout = 10; //10ms
        if (zmq_setsockopt(pSock, ZMQ_RCVTIMEO, &rcvTimeout, sizeof(rcvTimeout)) < 0)
        {
            zmq_close(pSock);
            std::cout << "error set sock option!" << std::endl;
            std::cout << "exit updateHook!" << std::endl;
            return;
        }
        if (zmq_bind(pSock, "ipc://stateMechine.ipc") < 0)
        {
            zmq_close(pSock);
            std::cout << "error connect!" << std::endl;
            std::cout << "exit updateHook!" << std::endl;
            return;
        }
        while (!stopFlag)
        {
            //获取消息
            //消息处理,添加状态字
            switch (mechine_state)
            {
            case M_INITIAL:
                mechine_state = M_RUNNING;
                break;
            case M_RUNNING:
                break;
            default:
                std::cout << " 没有这个状态!" << std::endl;
            }
            //检测消息是否有效
            //
            if (recvMsg(pSock, msgHolder))
            {
                baseInstance = praseCmdtoModule(msgHolder);
                if (baseInstance != nullptr)
                    (*baseInstance)();
                replyMessage();
            }
        }
        zmq_close(pSock);
        std::cout << "exit updateHook!" << std::endl;
        return;
    }
}