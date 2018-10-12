#include "motionCommands.hpp"
#include "../robotStateMechine/robotStateMechine.hpp"

bool motionCmdAddLine::run(std::vector<autoValue> params)
{
    std::cout << "motion cmd add line!" << std::endl;
    return true;
};
bool motionCmdAddLine::run(Json::Value &jsonData)
{
    motion *motionptr;
    // motion::getNum();
    motionptr = dynamic_cast<motion *>(robotStateMechine::getModuleBasePtr());
    std::cout << "motion cmd add line:" << motionptr->line_num++ << "  " << jsonData["message"].asString() << std::endl;
    return true;
};