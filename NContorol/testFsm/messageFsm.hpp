#include <iostream>
#include <vector>
#include "fsm.h"
class moduleBase;
//绑定监听端口
class messageStateBase
{
  public:
    messageStateBase() {}
    ~messageStateBase() {}
    void operator()();

  private:
    //解析消息返回类的实例
    void parseCommand(char *buf);
    moduleBase *modulebase;
};

class messageInitState : public messageStateBase
{
    void run();
};
class messageErrorState : public messageStateBase
{
    void run();
};

class messageWarningState : public messageStateBase
{
    void run();
};

class messageRunningState : public messageStateBase
{
    void run();
};

class messageFsm : public fsmlite::fsm<messageFsm>
{
    friend class fsm;

  public:
    enum states
    {
        M_INITIAL,
        M_ERROR,
        M_WARNING,
        M_RUNNING,
    };
    messageFsm(state_type init_state = M_INITIAL) : fsm(init_state)
    {
    }
    ~messageFsm() {}
    struct msg_t
    {
    };
    void messageMechineHook()
    {
        stateInstance->run();
    };
    bool isChanelInitial(msg_t &msg);
    bool isChanelError(msg_t &msg);
    bool isChanelWarning(msg_t &msg);
    bool isChanelRunning(msg_t &msg);

  private:
    using transition_table = table<>;
    messageStateBase *stateInstance;
};

void test()
{

    while (1)
    {
        switch (state)
        {
        case init:
            break;
        case error:
            break;
        case running:
            //得到模块
            char *buf;
            //消息转为json存于moduleBase中
            modulbase = parseCommand(buf);
            //解析消息,根据具体消息调用具体方法
            modulbase();
            json::Value root = moduleBase->getResult();
            resultProcess(root);

            break;
        }
    }
}