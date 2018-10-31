#include "motionCommands.hpp"
#include "../robotStateMechine/robotStateMechine.hpp"

bool motionCmdAddLine::run(Json::Value &jsonData)
{
    motion *motionptr;
    //调用相关方法
    motionptr = dynamic_cast<motion *>(robotStateMechine::getModuleBasePtr());
    std::cout << "motion: cmd add line:" << motionptr->line_num++ << "  " << jsonData["param2"].asString() << "count: " << jsonData["param1"].asInt() << std::endl;
    Json::Value jsonReply;
    char line_num[10];
    snprintf(line_num, sizeof(line_num), "%d", motionptr->line_num);
    std::string msg = "cmd motion add line done:" + std::string(line_num) + std::string("!");
    //设置返回值
    jsonReply["message"] = msg;
    motionptr->setReply(jsonReply);
    usleep(1000);
    return true;
};

bool motionCmdQueryTemperature::run(Json::Value &jsonData)
{
    motion *motionptr;
    //调用相关方法
    motionptr = dynamic_cast<motion *>(robotStateMechine::getModuleBasePtr());
    std::cout << "motion: cmd query temperature: " << jsonData["message"].asString() << std::endl;
    Json::Value jsonReply;
    std::string msg = "the temperature is 40 degree!";
    //设置返回值
    jsonReply["message"] = msg;
    motionptr->setReply(jsonReply);
    return true;
}