#pragma once
#include <iostream>
#include <list>
#include <jsoncpp/json/json.h>
#include "actionBase.hpp"

class moduleBase
{
  // friend actionBase;

public:
  moduleBase()
  {
    needReply = false;
  }
  ~moduleBase() {}
  virtual void operator()() = 0;
  virtual actionBase *praseCmdtoAction(Json::Value JsonCmd) = 0;
  // bool MsgToParams(Json::Value, std::vector<autoValue> param); //将消息参数提取出来,格式待定,可以是第一个参数命令号...
  bool MsgRely();
  bool getMessage(Json::Value &msg)
  {
    messageHolder = msg;
    return true;
  };

protected:
  bool getReply(Json::Value &msg);
  actionBase *cmdBase;
  bool needReply;
  Json::Value messageHolder;
  Json::Value messageReply;
};