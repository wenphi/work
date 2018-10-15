#include <zmq.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <csignal>
#include <jsoncpp/json/json.h>
#include <fstream>
// #include <malloc.h>

void stop(int sig);

//发送字符串函数
int s_send(void *socket, Json::Value &jsonMsg)
{
    int rc;
    std::string str = jsonMsg.toStyledString();
    char *cstr = const_cast<char *>(str.c_str());
    zmq_msg_t message;
    zmq_msg_init_size(&message, strlen(cstr));
    memcpy(zmq_msg_data(&message), cstr, strlen(cstr));
    rc = zmq_sendmsg(socket, &message, 0);
    zmq_msg_close(&message);
    return (rc);
}
int s_sendMore(void *socket, std::string &msg)
{
    int rc;
    char *cstr = const_cast<char *>(msg.c_str());
    zmq_msg_t message;
    zmq_msg_init_size(&message, strlen(cstr));
    memcpy(zmq_msg_data(&message), cstr, strlen(cstr));
    rc = zmq_sendmsg(socket, &message, ZMQ_SNDMORE);
    zmq_msg_close(&message);
    return (rc);
}
//接收字符串函数
bool s_recv(void *socket, Json::Value &jsonMsg)
{
    Json::Reader reader;
    zmq_msg_t message;
    zmq_msg_init(&message);
    if (zmq_recvmsg(socket, &message, 0) < 0)
    {
        zmq_msg_close(&message);
        return false;
    }
    int size = zmq_msg_size(&message);
    char *str = (char *)malloc(size + 1);
    memcpy(str, zmq_msg_data(&message), size);
    zmq_msg_close(&message);
    str[size] = 0;
    if (reader.parse(str, jsonMsg))
    {
        // std::cout << "rcv:" << str << std::endl;
        return true;
    }
    else
    {
        // std::cout << "rcv:" << str << std::endl;
        return false;
    }
}

bool s_recvDealer(void *socket, std::string &address, Json::Value &jsonData)
{

    Json::Reader reader;
    zmq_msg_t message;
    //收第一帧地址
    zmq_msg_init(&message);
    if (zmq_recvmsg(socket, &message, ZMQ_RCVMORE) < 0)
    {
        zmq_msg_close(&message);
        return false;
    }
    int size = zmq_msg_size(&message);
    char *str = (char *)malloc(size + 1);
    memcpy(str, zmq_msg_data(&message), size);
    zmq_msg_close(&message);
    str[size] = 0;
    address = std::string(str);
    // std::cout << "get address:" << str << std::endl;
    free(str);
    //收第二帧数据
    zmq_msg_init(&message);
    if (zmq_recvmsg(socket, &message, 0) < 0)
    {
        zmq_msg_close(&message);
        return false;
    }
    size = zmq_msg_size(&message);
    str = (char *)malloc(size + 1);
    memcpy(str, zmq_msg_data(&message), size);
    zmq_msg_close(&message);
    str[size] = 0;
    if (!reader.parse(str, jsonData))
        // std::cout << "rcv:" << str << std::endl;
        return false;
    // std::cout << msg << std::endl;
    return true;
}
//接收字符串函数
bool s_recvMore(void *socket, std::string &msg)
{
    Json::Reader reader;
    zmq_msg_t message;
    zmq_msg_init(&message);
    if (zmq_recvmsg(socket, &message, ZMQ_RCVMORE) < 0)
    {
        zmq_msg_close(&message);
        return false;
    }
    int size = zmq_msg_size(&message);
    char *str = (char *)malloc(size + 1);
    memcpy(str, zmq_msg_data(&message), size);
    zmq_msg_close(&message);
    str[size] = 0;
    msg = std::string(str);
    // std::cout << msg << std::endl;
    return true;
}
//
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