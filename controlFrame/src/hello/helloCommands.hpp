#pragma once
#include <iostream>
#include "../base/moduleBase.hpp"

class helloCmdTest : public actionBase
{
    bool run(Json::Value &jsonData);
};
