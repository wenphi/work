#include "ioCommands.hpp"
#include "io.hpp"
#include "../robotStateMechine/robotStateMechine.hpp"

bool ioCmdReadDiBit::run(Json::Value &jsonData)
{
    io *ioptr;
    //调用相关方法
    ioptr = dynamic_cast<io *>(robotStateMechine::getModuleBasePtr());
    //do
    std::cout << "io: cmd read di bit:" << ioptr->bitState << "  " << jsonData["message"].asString() << std::endl;

    //设置返回值
    Json::Value jsonReply;
    char cmsg[100];
    snprintf(cmsg, sizeof(cmsg), "the Di bit is:%d", ioptr->bitState);
    jsonReply["message"] = cmsg;
    ioptr->setReply(jsonReply);
    return true;
};

bool ioCmdwriteDiBit::run(Json::Value &jsonData)
{
    io *ioptr;
    //调用相关方法
    ioptr = dynamic_cast<io *>(robotStateMechine::getModuleBasePtr());
    //do
    std::cout << "io: cmd wite Di bit :" << jsonData["data"].asInt() << "  " << jsonData["message"].asString() << std::endl;
    ioptr->bitState = jsonData["data"].asInt();
    //设置返回值
    Json::Value jsonReply;
    std::string msg = "cmd write Di bit done!";
    jsonReply["message"] = msg;
    ioptr->setReply(jsonReply);
    return true;
}