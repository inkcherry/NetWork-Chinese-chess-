#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <vector>
#include <sys/ioctl.h>
class IKTCP_CLIENT
{
public:
    IKTCP_CLIENT(const std::string &address ,const  int &port);
    IKTCP_CLIENT(const std::string &address ,const  int &port,bool isunblock);
    bool Send(const std::string &buffer);
    std::string Recv(const int buffer_len=128);
    void set_block_config(bool isunblock);  //设置阻塞属性 0为阻塞 1为非阻塞
private:
    std::string address;
    void _init_unblcok_sock();//定义阻塞或者非阻塞模式
    void _init_block_sock();//定义阻塞或者非阻塞模式

    void _init_connect(const std::string &address,const int &port);
    int iksock;

    int port;
    sockaddr_in addr;

};