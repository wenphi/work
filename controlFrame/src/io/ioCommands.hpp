#pragma once
#include <iostream>
#include "../base/moduleBase.hpp"

class ioCmdwriteDiBit : public actionBase
{
    bool run(Json::Value &jsonData);
};

class ioCmdReadDiBit : public actionBase
{
    bool run(Json::Value &jsonData);
};