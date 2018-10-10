#include <zmq.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <csignal>
#include <thread>
#include <vector>
#include <jsoncpp/json/json.h>
#include <fstream>
// #include <malloc.h>

void stop(int sig);

//发送字符串函数
int s_send(void *socket, char *string)
{
    int rc;
    zmq_msg_t message;
    zmq_msg_init_size(&message, strlen(string));
    memcpy(zmq_msg_data(&message), string, strlen(string));
    rc = zmq_sendmsg(socket, &message, 0);
    zmq_msg_close(&message);
    return (rc);
}
//接收字符串函数
static char *s_recv(void *socket)
{
    char *str = (char *)" ";
    zmq_msg_t message;
    zmq_msg_init(&message);
    if (zmq_recvmsg(socket, &message, 0) < 0)
    {
        std::cout << "wait out time" << std::endl;
        return str;
    }
    int size = zmq_msg_size(&message);
    char *string = (char *)malloc(size + 1);
    memcpy(string, zmq_msg_data(&message), size);
    zmq_msg_close(&message);
    string[size] = 0;
    return (string);
}

//

char *encodeCommand(int cmd, std::string message)
{
    Json::Value jsonCmd;
    jsonCmd["cmd"] = cmd;
    jsonCmd["data"] = message;
    std::string result = jsonCmd.toStyledString();
    return const_cast<char *>(result.c_str());
}
Json::Value decodeCommand(char *data)
{
    Json::Value jsonCmd;
    Json::Reader reader;
    Json::Value jsonData;
    // std::ifstream is;
    // is.open(data, std::ios::binary);
    if (reader.parse(data, jsonData))
    {
        jsonCmd["cmd"] = jsonData["cmd"];
        jsonCmd["data"] = jsonData["data"];
    }
    return jsonCmd;
}
std::string getString(int num)
{
    switch (num)
    {
    case 0:
        return std::string("0");
    case 1:
        return std::string("1");
    case 2:
        return std::string("2");
    case 3:
        return std::string("3");
    case 4:
        return std::string("4");
    case 5:
        return std::string("5");
    case 6:
        return std::string("6");
    case 7:
        return std::string("7");
    case 8:
        return std::string("8");
    case 9:
        return std::string("9");
    default:
        return std::string("-1");
    }
}