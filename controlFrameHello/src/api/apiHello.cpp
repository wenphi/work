#include "apiHello.hpp"

void apiHello::setHello(int num)
{
    messageClient *msgClient = new messageClient(address, "setHello");
    Json::Value jsonData;
    jsonData["msgType"] = msgtype_t::MSG_CMD;
    jsonData["module"] = msgModule_t::MSG_MODULE_HELLO;
    jsonData["needReply"] = false;
    jsonData["msgData"]["cmd"] = 0;
    jsonData["msgData"]["params"]["param1"] = num;
    msgClient->sendJson(jsonData);
    delete msgClient;
}

int apiHello::readHello()
{
    messageClient *msgClient = new messageClient(address, "readHello");
    Json::Value jsonData;
    jsonData["msgType"] = msgtype_t::MSG_CMD;
    jsonData["module"] = msgModule_t::MSG_MODULE_HELLO;
    jsonData["needReply"] = true;
    jsonData["msgData"]["cmd"] = 1;
    msgClient->sendJson_block(jsonData);
    jsonData = msgClient->recvJson_block();
    int num = jsonData["replyMessage"]["reply"]["param1"].asInt();
    delete msgClient;
    return num;
}