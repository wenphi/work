#pragma once
#include "../base/moduleBase.hpp"
#include "robotkdl/robotKdl.hpp"
#include "motionCommands.hpp"

class motion : public moduleBase
{
public:
  motion() : kdl(), line_num(0){};
  ~motion() {}
  //解析返回子类指针
  actionBase *praseCmdtoAction(Json::Value jsonCmd);
  //motion的同步钩子
  void motionHook();
  int line_num;

public:
  int getNum()
  {
    return line_num;
  }

private:
  //motio配置文件
  Json::Value cfg;
  //
  //运动队列
  //
  //测试数值
  robotKdl kdl;
};