#pragma once
#include "../base/moduleBase.hpp"
#include "helloCommands.hpp"

class hello : public moduleBase
{
  public:
    hello(){};
    ~hello(){};

    //解析返回子类指针--重载
    actionBase *praseCmdtoAction(Json::Value jsonCmd);

    /*其他函数*/
    void printHook()
    {
        for (auto data : vectorInt)
            std::cout << data << " ";
        std::cout << std::endl;
    }
    bool helloAppend(int numInt)
    {
        vectorInt.push_back(numInt);
        return true;
    };

  protected:
  private:
    //配置文件
    Json::Value cfg;
    //测试队列
    std::vector<int> vectorInt;
};