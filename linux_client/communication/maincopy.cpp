
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#define TTY_PATH            "/dev/tty"
#define STTY_US             "stty raw -echo -F "
#define STTY_DEF            "stty -raw echo -F "
 char buffer[64]=""; //缓冲数组
 int buffer_index=0;
 int ch = 0;
 int buffer_len=sizeof(buffer);
 int get_char()   //static
{ 
    fd_set rfds;
    struct timeval tv;
    char ch = 0;

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 10; //设置等待超时时间

    //检测键盘是否有输入
    if (select(1, &rfds, NULL, NULL, &tv) > 0)
    {
        ch = getchar(); 
        printf("%c\n\r",ch);
        buffer[buffer_index]=(char)ch;
        buffer_index++;
    }
    return ch;
}
void unblock_cin()
{
    ch = get_char();
        if (ch)
        {
            switch (ch)
            {
                case 'q':          //q退出
                    system(STTY_DEF TTY_PATH);exit(0);
                case 13:           //
                    {   
                    
                        buffer[buffer_index-1]='\0';
                        std::cout<<"发送数组"<<buffer<<"\n\r";
                        memset(buffer,0,buffer_len);
                        buffer_index=0; 
                        break;
                    }
            
            }
        }           
}

int main()
{
    int ch = 0;
    system(STTY_US TTY_PATH);
    while(1)
    { unblock_cin();   
    }
}