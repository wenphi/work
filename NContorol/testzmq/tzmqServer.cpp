#include <zmq.h>
#include <iostream>
using namespace std;
int main()
{
    //创建上下文
    void *pctx = zmq_ctx_new();
    if (pctx == NULL)
    {
        cout << "create ctx failed!" << endl;
        return 0;
    }
    //创建套接字
    void *psock = zmq_socket(pctx, ZMQ_DEALER);
    if (psock == NULL)
    {
        cout << "create sock failed!" << endl;
        zmq_ctx_destroy(pctx);
        return 0;
    }
    //设置超时时间
    int rcvTimeout = 5000;
    if (zmq_setsockopt(psock, ZMQ_RCVTIMEO, &rcvTimeout, sizeof(rcvTimeout)))
    {
        cout << "set timeout error!" << endl;
        zmq_close(psock);
        zmq_ctx_destroy(pctx);
        return 0;
    }
    //使用tcp通信
    const char *paddr = "tcp://*:7766";
    if (zmq_bind(psock, paddr) < 0)
    {
        cout << "bind address error!" << endl;
        zmq_close(psock);
        zmq_ctx_destroy(pctx);
        return 0;
    }
    while (1)
    {
        char szMsg[1024] = {0};
        printf("waitting...\n");
        errno = 0;
        //循环等待接收到来的消息，当超过5秒没有接到消息时，
        //zmq_recv函数返回错误信息 ，并使用zmq_strerror函数进行错误定位
        if (zmq_recv(psock, szMsg, sizeof(szMsg), 0) < 0)
        {
            printf("error = %s\n", zmq_strerror(errno));
            continue;
        }
        printf("received message : %s\n", szMsg);
    }
}