#pragma once
#include "libjsoncpp/include/json.h"
#include "../message/messageClient.hpp"
#include "../base/stateBase.hpp"

class apiHello
{
  public:
    apiHello(std::string address_)
    {
        address = address_;
    };
    ~apiHello(){};

    void setHello(int num);

    int readHello();

  private:
    std::string address;
};