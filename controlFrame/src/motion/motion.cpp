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
        // std::cout << "motion recv: " << jsonCmd.toStyledString() << std::endl;
        root = jsonCmd["params"];
        // std::cout << "in motion prase: " << root["message"].asString() << " " << root["data"].asInt() << std::endl;
        cmdbase_->setParams(root);
    }
    return cmdbase_;
};