#pragma once
#include "../motion/motion.hpp"

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
    robotStateMechine() : motionInstance()
    {
        mechine_state = M_INITIAL;
        stopFlag = false;
    };
    ~robotStateMechine(){};

    void updateHook();
    //得到指定模块子类
    moduleBase *praseCmdtoModule(Json::Value &msg);
    //消息处理(待定)
    bool getContext(void *ctx_)
    {
        pCtx = ctx_;
    }
    bool recvMsg(void *sock, Json::Value &jsonMsg); //优化
    bool replyMessage() { return true; };
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
    void *pCtx;
    M_STATE mechine_state;
    static moduleBase *baseInstance;
    motion motionInstance;
    Json::Value msgHolder;
    Json::Value msgReply;
};
