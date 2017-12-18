#include "utility.h"

std::map<int,std::pair<std::string,int> > name_pool;  //第二pair表示己方以及对手fd
struct epoll_event event;   // 告诉内核要监听什么事件    
struct epoll_event wait_event; //内核监听完的结果  
int sockfd ;  //1.创建tcp监听套接字  
int fd[OPEN_MAX];
int i,maxi,ret;   
int epfd;

//状态信息
#define TIPS_S_PY "#100"
#define TIPS_S_OP "choose opponent success"            //choose Opponent success; 
#define TIPS_S_LO "login success,set your name"        //login success;
const std::string TIPS_S_SP ="success to match opponent";
const std::string TIP_S_BE_SP="challenge a contest\n\r";   //被挑战
//提示信息
#define TIPS_S_NA "set your name"                      //set name
const std::string TIPS_C_OP="please choose an opp or wait for connection\n\r";

void gfun::Send(int fd,std::string &str)
{
send(fd,str.c_str(),str.length(),0);
}
void gfun::Send(int fd,std::string &&str) //这里仍然要当作左值用
{
send(fd,str.c_str(),str.length(),0);
}
void gfun::initaddr()
{   
     sockfd = socket(AF_INET, SOCK_STREAM, 0);  
      //2.绑定sockfd  
    struct sockaddr_in my_addr;  
    bzero(&my_addr, sizeof(my_addr));  
    my_addr.sin_family = AF_INET;  
    my_addr.sin_port = htons(8002);  
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);  
    bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));  
        
    //3.监听listen  
    listen(sockfd, 10);  
        
    //4.epoll相应参数准备  
    
    i = 0, maxi = 0;  
    memset(fd,-1, sizeof(fd));  
    fd[0] = sockfd;  
        
     epfd = epoll_create(10); // 创建一个 epoll 的句柄，参数要大于 0， 没有太大意义    
    if( -1 == epfd ){    
        perror ("epoll_create");    
        exit(-1);   
    }    
        
    event.data.fd = sockfd;     //监听套接字    
    event.events = EPOLLIN; // 表示对应的文件描述符可以读  
        
    //5.事件注册函数，将监听套接字描述符 sockfd 加入监听事件    
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);    
    if(-1 == ret){    
        perror("epoll_ctl");    
        exit(-1);    
    }   
    std::cout<<"server running "<<std::endl;
    //6.对已连接的客户端的数据处理  
}


void gfun::run()
{
    while(1){
     // 监视并等待多个文件（标准输入，udp套接字）描述符的属性变化（是否可读）    
        // 没有属性变化，这个函数会阻塞，直到有变化才往下执行，这里没有设置超时     
        ret = epoll_wait(epfd, &wait_event, maxi+1, -1);   
            
        //6.1监测sockfd(监听套接字)是否存在连接  
        if(( sockfd == wait_event.data.fd )     
            && ( EPOLLIN == wait_event.events & EPOLLIN ) )  
        {  
            struct sockaddr_in cli_addr;  
            socklen_t clilen = sizeof(cli_addr);  
                
            //6.1.1 从tcp完成连接中提取客户端  
            int connfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen); 
             
            gfun::Send(connfd,TIPS_S_LO);
            name_pool.insert(std::make_pair(connfd,std::pair<std::string,int>("",-1)));
            // std::cout<<"为"<<connfd<<"插入一个数据"<<std::endl;

            //6.1.2 将提取到的connfd放入fd数组中，以便下面轮询客户端套接字  
            for(i=1; i<OPEN_MAX; i++)  
            {  
                if(fd[i] < 0)  
                {  
                    fd[i] = connfd;                      
                    event.data.fd = connfd; //监听套接字    
                    event.events = EPOLLIN; // 表示对应的文件描述符可以读 
                        
                    //6.1.3.事件注册函数，将监听套接字描述符 connfd 加入监听事件    
                    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &event);    
                    if(-1 == ret){    
                        perror("epoll_ctl");    
                        exit(-1);    
                    }   
                    break;  
                }  
            }  
                
            //6.1.4 maxi更新  
            if(i > maxi)  
                maxi = i;  
                    
            //6.1.5 如果没有就绪的描述符，就继续epoll监测，否则继续向下看  
            if(--ret <= 0)  
                continue;  
        }  
            
        //6.2继续响应就绪的描述符  
        for(i=1; i<=maxi; i++)  
        {  
            if(fd[i] < 0)  
                continue;  
                
            if(( fd[i] == wait_event.data.fd )     
            && ( EPOLLIN == wait_event.events & (EPOLLIN|EPOLLERR) ))  
            {  
                int len = 0;  
                char buf[128] ="";  
                    
                //6.2.1接受客户端数据  
                if((len = recv(fd[i], buf, sizeof(buf), 0)) < 0)  
                {  
                    if(errno == ECONNRESET)//tcp连接超时、RST  
                    {  
                        close(fd[i]);  
                        fd[i] = -1;  
                    }  
                    else  
                        perror("read error:");  
                }  
                else if(len == 0)//客户端关闭连接  
                {   std::cout<<"断开连接";
                    close(fd[i]);  
                    fd[i] = -1;  
                    auto iter=name_pool.find(fd[i]);
                    
                }  
                else//正常接收到服务器的数据  
                {   
                    auto cur_user=name_pool.find(fd[i]);
                    std::cout<<"收到用户："<<cur_user->second.first<<" 数据  "<<buf<<std::endl;
                    // send(fd[i], buf, len, 0);  

                    std::string msg(buf);
                    gfun::deal_msg(cur_user,msg);
                } 
                //6.2.2所有的就绪描述符处理完了，就退出当前的for循环，继续poll监测  
                if(--ret <= 0)  
                    break;  
            }  
        }  
    }
}
void gfun::deal_msg(decltype(name_pool.begin()) &iter,std::string &msg)
{  
  if(iter==name_pool.end())                   //错误提示
  std::cout<<"error:none user"<<std::endl;

  else if(iter->second.first=="")            //命名成功提示及选择对手
  {    
      std::cout<<"set name"<<std::endl; 
      iter->second.first=msg;
      gfun::Send(iter->first,gfun::get_user_table()+TIPS_C_OP);
      return ;
  }
  else if(iter->second.second<0)         //向对手发送请求  ！！！此处暂不予服务器端msg格式检测         
  {   
      int op_fd=atoi(msg.c_str());
      std::cout<<"用户想要连接"<<op_fd<<std::endl;
      if(gfun::find(op_fd)>0)             //用户存在,ps:允许你自己跟你自己玩,只要你乐意
      {   
          iter->second.second=op_fd;  //连接当前选择用户这个
          auto op_iter=name_pool.find(op_fd);
          op_iter->second.second=iter->first;
          gfun::Send(op_fd,(iter->second.first)+TIP_S_BE_SP);
          gfun::Send(iter->first,TIPS_S_SP+(op_iter->second.first)+"\n\r");
   //发送状态码  唤醒客户端游戏进程     
          gfun::Send(op_fd,TIPS_S_PY);
          gfun::Send(iter->first,TIPS_S_PY);
      }          //!!!!此处暂为测试不予检测直接连接
      else {gfun::Send(op_fd,"#defaut sp");}
  }
  else   //gaming
  {
     gfun::Send(iter->second.second,msg);
  }  
      
}

std::string gfun::get_user_table()
{
      std::string all_users="users talbe:\n\r";
      for(auto iter=name_pool.begin();iter!=name_pool.end();++iter)
      {   if(((iter->second).second)<0)              //没有匹配的对手
          {all_users+=std::to_string(iter->first)+" :"+(iter->second.first)+"\n\r";}
        }
      return all_users;
}
int gfun::find(int &ta_fd) //返回目的sockfd的下标
{
    for(int i=0;i<OPEN_MAX;i++)
    {
        if(fd[i]==ta_fd)
        return i;
    }
    return -1;            //can not't find
}