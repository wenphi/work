#pragma once
#include <iostream>
#include "../base/moduleBase.hpp"

class motionCmdAddLine : public actionBase
{
    bool run(Json::Value &jsonData);
};

class motionCmdQueryTemperature : public actionBase
{
    bool run(Json::Value &jsonData);
};