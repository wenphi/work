#include "motion.hpp"

actionBase *motion::praseCmdtoAction(Json::Value jsonCmd)
{
    // std::vector<autoValue> params;
    // MsgToParams(jsonCmd, params);
    Json::Value root;
    actionBase *cmdbase_;
    switch (jsonCmd["cmd"].asInt())
    {
    case 0:
        cmdbase_ = new motionCmdAddLine;
        break;
    case 1:
        cmdbase_ = new motionCmdQueryTemperature;
        break;
    default:
        cmdbase_ = nullptr;
    }
    if (cmdbase_)
    {
        root = jsonCmd["params"];
        // std::cout << "in motion prase: " << root["message"].asString() << " " << root["data"].asInt() << std::endl;
        cmdbase_->setParams(root);
    }
    return cmdbase_;
};
void motion::operator()()
{
    cmdBase = praseCmdtoAction(messageHolder);
    if (cmdBase != nullptr)
    {
        cmdBase->start();
        delete cmdBase;
    }
    else
        std::cout << " motion接收到未知命令!" << std::endl;
}