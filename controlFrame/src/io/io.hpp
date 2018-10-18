#pragma once
#include "../base/moduleBase.hpp"
#include "ioCommands.hpp"

class io : public moduleBase
{
  public:
    io() : bitState(0){};
    ~io(){};
    //解析返回子类指针
    actionBase *praseCmdtoAction(Json::Value jsonCmd);
    //解析--运行--返回
    void operator()();
    //motion的同步钩子
    int bitState;

  protected:
  private:
    //motio配置文件
    Json::Value cfg;
    //
    //运动队列
    //
    //测试数值
};