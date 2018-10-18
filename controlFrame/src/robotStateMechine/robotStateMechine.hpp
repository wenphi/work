#pragma once
#include "../motion/motion.hpp"
#include "../io/io.hpp"
#include "../base/messageBase.hpp"

enum M_STATE
{
    M_INITIAL,
    M_ERROR,
    M_WARNING,
    M_RUNNING,

};
class robotStateMechine
{
  public:
    robotStateMechine(std::string serverAddress) : motionInstance(), ioInstance()
    {
        zmqServer = new messageServer(serverAddress);
        mechine_state = M_INITIAL;
        stopFlag = false;
    };
    ~robotStateMechine()
    {
        delete zmqServer;
    };

    void updateHook();
    //得到指定模块子类
    moduleBase *praseCmdtoModule(Json::Value &msg);

    //刷新状态
    void updateState() { return; };
    //消息处理(待定)

    bool replyMessage(Json::Value &jsonDate);
    bool msgToValue(char *buf, Json::Value &JsonCmd);
    bool msgToVector(char *buf, std::vector<autoValue> &params);
    static moduleBase *getModuleBasePtr();
    void setStop()
    {
        stopFlag = true;
    }
    void setStart()
    {
        stopFlag = false;
    }

  private:
    bool stopFlag;
    messageServer *zmqServer;
    M_STATE mechine_state;
    static moduleBase *baseInstance;
    motion motionInstance;
    io ioInstance;
    Json::Value msgHolder;
    Json::Value msgReply;
};
