#include <string.h>  
#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <sys/select.h>  
#include <sys/time.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <sys/epoll.h>  
#include <errno.h>  
#include <iostream>
#include <map>
#include <string>    
#define OPEN_MAX 100
//global var decleration
extern std::map<int,std::pair<std::string,int> > name_pool;  //第二pair表示己方以及对手fd
extern struct epoll_event event;   // 告诉内核要监听什么事件    
extern struct epoll_event wait_event; //内核监听完的结果  
extern int sockfd ;  //1.创建tcp监听套接字  
extern int fd[OPEN_MAX];
extern int i,maxi,ret;   
extern int epfd;

//global fun decleration
namespace gfun
{
void Send(int fd,std::string &str);
void Send(int fd,std::string &&str);
void initaddr();
void run();
void deal_msg(decltype(name_pool.begin()) &iter,std::string &msg);
int find(int &tar_fd);
std::string  get_user_table();
}
