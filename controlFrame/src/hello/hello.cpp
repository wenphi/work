#include "hello.hpp"

actionBase *hello::praseCmdtoAction(Json::Value jsonCmd)
{
    // std::vector<autoValue> params;
    // MsgToParams(jsonCmd, params);
    Json::Value root;
    actionBase *cmdbase_;
    switch (jsonCmd["cmd"].asInt())
    {
    case 0:
        cmdbase_ = new helloCmdTest;
        break;
    default:
        cmdbase_ = nullptr;
    }
    if (cmdbase_)
    {
        root = jsonCmd["params"];
        cmdbase_->setParams(root);
    }
    return cmdbase_;
};