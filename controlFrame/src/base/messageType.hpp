#pragma once
#include <iostream>

enum msgModule_t
{
    MSG_MODULE_MOTION,
    MSG_MODULE_IO,
    MSG_MODULE_HELLO,
};

enum motionCmd_t
{
    MSG_CMD_MOTION_ADD_LINE,
    MSG_CMD_MOTION_QUERY_TEMPERATURE,
};
