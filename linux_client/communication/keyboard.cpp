#include "keyboard.h" 

keyboard::keyboard(IKTCP_CLIENT &cln_):buffer(""),buffer_index(0),ch(0),buffer_len(sizeof(buffer)),cln(cln_)
{

}
int keyboard::get_char()   //static
{ 
    fd_set rfds;
    struct timeval tv;
    ch = 0;

    FD_ZERO(&rfds);
    FD_SET(0, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 10; //设置等待超时时间

    //检测键盘是否有输入
    if (select(1, &rfds, NULL, NULL, &tv) > 0)
    {  
        ch = getchar(); 
        if(ch!=127)
       {
           buffer[buffer_index]=(char)ch;
        buffer_index++;}

        else{  //退格
          
            buffer[buffer_index-1]='\0';
            buffer_index-=1;
        }
    }
    return ch;
}
void keyboard::unblock_cin()
{
    ch = get_char();
        if (ch)
        {   printf("\r\n%s\r\n",buffer);
            switch (ch)
            {   
                case 'q':          //q退出
                    system(STTY_DEF TTY_PATH);exit(0);
                case 13:           //回车 处理消息
                    {   
                        buffer[buffer_index-1]='\0';
                        std::cout<<"\r\nlocal:处理数据"<<buffer<<"\n\r";
                        cln.Send(buffer);
                        memset(buffer,0,buffer_len);
                        buffer_index=0; 
                        break;
                    }
            }
        }           
}