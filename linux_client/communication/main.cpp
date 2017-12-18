
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include "keyboard.h"
#include "IKTCP_CLIENT.h"
#include "package.h"


int main()
{   
    package pac;
    IKTCP_CLIENT cln("127.0.0.1",8002,1);  //客户端连接对象
    keyboard m(cln);                       //非阻塞select 用户输入对象
    system(STTY_US TTY_PATH);
    std::string str;
    while(1)
    {    
        // std::cout<<"运行"<<std::endl;
            m.unblock_cin();
            str=cln.Recv();
            if(str!="")
            {
               pac.deal_msg(str);
            }
    }
    return 0;
}