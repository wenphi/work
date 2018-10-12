#pragma once
#include <iostream>
#include "../base/moduleBase.hpp"

class motionCmdAddLine : public actionBase
{
    bool run(std::vector<autoValue> params);
    bool run(Json::Value &jsonData);
};