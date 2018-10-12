
/*说明
*每个模块继承modulebase
*{
    module:0,
    cmd:0,
    date:[
        {},
    ]
}
*/

#include <iostream>
#include <unistd.h>
#include <list>
#include <jsoncpp/json/json.h>
using namespace std;

//消息类

class robotMessege
{
  public:
    robotMessege(){};
    ~robotMessege(){};
    bool send();
    bool recv();
};
class autoValue;
class robotKdl
{
  public:
    robotKdl() {}
    ~robotKdl() {}
};

class actionBase
{
  public:
    actionBase() {}
    ~actionBase() {}
    //子类调用
    void start()
    {
        run(actionParams);
    }
    bool setParams(std::vector<autoValue> params_)
    {
        std::copy(params_.begin(), params_.end(), std::back_inserter(actionParams));
        return true;
    };

  private:
    virtual bool run(std::vector<autoValue> params) = 0;
    std::vector<autoValue> actionParams;
};

class moduleBase
{
  public:
    moduleBase(){};
    ~moduleBase(){};
    virtual void operator()();
    virtual actionBase *praseComdtoAction(Json::Value JsonCmd);
    bool MsgToParams(Json::Value, std::vector<autoValue> param); //将消息参数提取出来,格式待定,可以是第一个参数命令号...
    bool MsgRely();

  protected:
    bool getMessage(Json::Value &msg);
    bool getReply(Json::Value &msg);
    actionBase *cmdBase;
    bool needReply;
    Json::Value messageHolder;
    Json::Value messageReply;
};
//motion模块
class motionCmdAddLine : public actionBase
{
    bool run(std::vector<autoValue> params)
    {
        cout << "motion cmd add line" << endl;
        return true;
    };
};
class motion : public moduleBase
{
  public:
    motion() : kdl(){};
    ~motion() {}
    //解析返回子类指针
    actionBase *praseCmdtoAction(Json::Value jsonCmd)
    {
        std::vector<autoValue> params;
        MsgToParams(jsonCmd, params);
        actionBase *cmdbase_ = new motionCmdAddLine;
        if (cmdbase_)
            cmdbase_->setParams(params);
        return cmdbase_;
    };

    //解析--运行--返回
    void operator()()
    {
        cmdBase = praseCmdtoAction(messageHolder);
        cmdBase->start();
        delete cmdBase;
    };
    //motion的同步钩子
    void motionHook();

  private:
    //motio配置文件
    Json::Value cfg;
    //
    //运动队列
    //
    robotKdl kdl;
};

//状态机

class robotStateMechine
{
  public:
    robotStateMechine(){};
    ~robotStateMechine(){};
    enum
    {
        M_INITIAL,
        M_ERROR,
        M_WARNING,
        M_RUNNING,

    } M_STATE;

    void updateHook()
    {
        //获取消息
        recvMsg(msgHolder);
        //消息处理,添加状态字
        switch (M_STATE)
        {
        case M_INITIAL:
            break;
        case M_RUNNING:
            break;
        default:
            cout << " 没有这个状态!" << endl;
        }
        //检测消息是否有效
        //
        baseInstance = praseCmdtoModule(msgHolder);
        if (baseInstance)
            (*baseInstance)();
        replyMessage();
    };
    //得到指定模块子类
    moduleBase *praseCmdtoModule(Json::Value &msg)
    {
        //根据参数进行选取子类
        //指向子类
        baseInstance = &motionInstance;
        //baseInstance =&ioInstance;
        return baseInstance;
    };
    //消息处理
    bool recvMsg(Json::Value); //优化
    bool replyMessage();
    bool msgToValue(char *buf, Json::Value &JsonCmd);
    bool msgToVector(char *buf, std::vector<autoValue> &params);

  private:
    moduleBase *baseInstance;
    motion motionInstance;
    Json::Value msgHolder;
    Json::Value msgReply;
};

///////////////////////////////////////////////////////////
class a
{
  public:
    a(){};
    ~a(){};
    virtual void p()
    {
        cout << "in a" << endl;
    };
};
class b : public a
{
  public:
    void p()
    {
        cout << "in b" << endl;
    }
    void k()
    {
        cout << " new function int b" << endl;
    }
};
int main()
{
    const char *data = "is b";
    a *a_;
    a ia;
    a_ = &ia;
    // if (tbase != nullptr)
    cout << &(*a_) << endl;
    a_->p();
    a_ = new b;
    b *b_ = dynamic_cast<b *>(a_);
    b_->p();
    b_->k();
    delete a_;
    cout << a_ << endl;
    // (*tbase)();
    // cin >> data;
}