#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include "IKTCP_CLIENT.h"  //keyboard接受client构造 用以处理函数
#define TTY_PATH            "/dev/tty"
#define STTY_US             "stty raw -echo -F "
#define STTY_DEF            "stty -raw echo -F "
class keyboard{
private:
    IKTCP_CLIENT cln;
    char buffer[64]; //缓冲数组
    int buffer_index;
    int ch ;
    int buffer_len;
    int get_char();
public:
    keyboard(IKTCP_CLIENT &cln);
    void unblock_cin();
};
