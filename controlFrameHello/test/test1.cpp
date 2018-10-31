#include "robotStateMechine/robotStateMechine.hpp"
#include "api/apiHello.hpp"
#include "libjsoncpp/include/json.h"
#include <csignal>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

bool stopFlag = false;
moduleBase *robotStateMechine ::baseInstance = nullptr;
std::string taddress = "ipc:///home/ywh/stateMechine.ipc";

void stop(int sig)
{
    if (sig)
        stopFlag = true;
}

int main()
{
    std::vector<std::thread> threads;
    signal(SIGINT, stop);
    apiHello *apitest = new apiHello(taddress);
    for (int i = 0; i <= 1000; i++)
    {
        apitest->setHello(i);
        std::cout << "send:" << i << std::endl;
        std::cout << "recv:" << apitest->readHello() << std::endl;
        // usleep(1000);
    }
    delete apitest;
    std::cout << "apiTest exit done!" << std::endl;
    return 0;
}