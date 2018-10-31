#pragma once
#include "../hello/hello.hpp"
#include "../motion/motion.hpp"
#include "../io/io.hpp"
#include "../base/messageBase.hpp"
#include "../base/messageType.hpp"
#include "../base/stateBase.hpp"
#include "robotStates.hpp"

class robotStateMechine
{
  public:
    robotStateMechine(std::string serverAddress) : motionInstance(), ioInstance(), helloInstance()
    {
        zmqServer = new messageServer(serverAddress);
        preStateBase = new stateInit();
        stopFlag = false;
    };
    ~robotStateMechine()
    {
        delete zmqServer;
        delete preStateBase;
    };

    void updateHook();
    //返回基类指针
    static moduleBase *getModuleBasePtr();
    void setStop() { stopFlag = true; }
    void setStart() { stopFlag = false; }
    //
    void test()
    {
        static int a = 0;
        std::cout << "in robot state mechine:" << a++ << std::endl;
    }

  protected:
    //得到指定模块子类
    moduleBase *praseCmdToModule();
    //刷新状态
    void updateStateHolder(Json::Value) { return; };

    //new test
    bool recvMessage();
    bool replyMessage();

  public:
    /*模块实例*/
    hello helloInstance;
    motion motionInstance;
    io ioInstance;

  private:
    bool stopFlag;                   //退出标志位
    msgHolder_t msgHolder;           //消息数据保存结构体
    replyHolder_t replyHolder;       //应答数据保存结构体
    stateHolder_t stateHolder;       //状态字保存结构体
    messageServer *zmqServer;        //zmq服务端
    stateBase *preStateBase;         //当前状态
    stateBase *nextStateBase;        //下一状态
    static moduleBase *baseInstance; //模块基类指针
};
