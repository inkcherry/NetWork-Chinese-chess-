
#include "package.h"
package::package(IKTCP_CLIENT &cln_):is_gaming(false),p_deal_msg(&package::deal_msg_from_server),main_cln(&cln_){
 main_checkerboard=new checkerboard(); 
}
const char * package::split_symbol=",";

void package::deal_msg_from_server(std::string &msg){
    
    std::cout<<msg.substr(0,4)<<std::endl;
    std::cout<<"------------------in connection "<<"\n\r";
   
    if(msg.substr(0,4)=="#100")
    {
        is_gaming=1;
        std::cout<<"now start playing"<<"\n\r";
        if(msg.substr(4,1)=="1")            //先手
        {   std::cout<<"我是先手"<<"\n";
            deal_msg_from_client_in_gaming();
        }
        else 
        {
            std::cout<<"我是后手"<<"\n";
        }
        p_deal_msg=&package::deal_msg_from_server_in_gaming;
        return;
    }
    std::cout<<"server :"<<msg<<"\n\r"; 

}
void package::deal_msg_from_client_in_gaming()
{   
    main_checkerboard->show_chessboard();
    while(true)
      {  int pos[4];   //from (y x)  to (y x);
        std::cout <<"选棋"<<"\n\r";
        std::cin>>pos[0]>>pos[1];
        if(main_checkerboard->select_chess(pos[0],pos[1]))
        {
            std::cout <<"移动" <<std::endl;
			std::cin >> pos[2] >> pos[3];
			if (main_checkerboard->move_chess(pos[2], pos[3]))  //移动成功
			{   main_checkerboard->show_chessboard();
                std::string chess_msg=std::to_string(pos[0]);
                for(int i=1;i<4;i++)
                chess_msg+=","+std::to_string(pos[i]);
                main_cln->Send(chess_msg);
              break;
            }
        }
    }
    
}
 void package::deal_msg_from_server_in_gaming(std::string &msg)
{   int pos[4];
    int i=0;
    
    char *num=strtok(const_cast<char *>(msg.c_str()),split_symbol);
    while(num)
    {
    pos[i]=atoi(num);
    std::cout<<"get "<<pos[i]<<"\n\r";    
    i++;
    num=strtok(NULL,split_symbol);
   }
   main_checkerboard->select_chess(pos[0],pos[1]);
   main_checkerboard->move_chess(pos[2],pos[3]);
   deal_msg_from_client_in_gaming();
}
void package::deal_msg(std::string &msg)
{   
    (this->*p_deal_msg)(msg);
}
// inline int to_int(char *c)
// {   
//     return *c-'0';
// }