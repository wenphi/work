#include "helloCommands.hpp"
#include "hello.hpp"
#include "../robotStateMechine/robotStateMechine.hpp"

bool helloCmdTest::run(Json::Value &jsonData)
{
    hello *helloptr;

    //指向hello模块
    helloptr = dynamic_cast<hello *>(robotStateMechine::getModuleBasePtr());
    //调用hello中的方法
    helloptr->helloAppend(jsonData["param1"].asInt());
    helloptr->printHook();
    //设置返回值
    Json::Value jsonReply;
    std::string smsg = "hello cmd done!";
    jsonReply["message"] = smsg;
    helloptr->setReply(jsonReply);
    return true;
};
