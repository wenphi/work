#include "robotStateMechine.hpp"
#include <cstdlib>
#include <cstring>
#include <unistd.h>

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
        break;
    case 1:
        baseInstance = &ioInstance;
        break;
    default:
        baseInstance = nullptr;
    }
    if (baseInstance != nullptr)
        baseInstance->setMessage(msg);
    return baseInstance;
}

void robotStateMechine::updateHook()
{

    while (!stopFlag)
    {
        //获取消息
        msgHolder = zmqServer->recvJson();
        //消息处理,添加状态字
        if (!msgHolder.isNull())
        {
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
            baseInstance = praseCmdtoModule(msgHolder);
            if (baseInstance != nullptr)
                (*baseInstance)();
            msgReply = baseInstance->outPutReply();
            replyMessage(msgReply);
        }
        else
        {
            std::cout << "do something else..." << std::endl;
            sleep(2);
        }
        //刷新状态
        updateState();
        usleep(10000);
    }
    std::cout << "exit updateHook!" << std::endl;
    return;
}
bool robotStateMechine::replyMessage(Json::Value &jsonDate)
{
    zmqServer->sendJson(jsonDate);
    return true;
}