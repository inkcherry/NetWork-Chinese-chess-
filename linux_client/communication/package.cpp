
#include "package.h"
package::package():is_gaming(false),p_deal_msg(&package::deal_msg_from_server){
}

void package::deal_msg_from_server(std::string &msg){
    
    std::cout<<msg.substr(0,4)<<"\n\r";
    std::cout<<"------------------in connection "<<"\n\r";
   
    if(msg.substr(0,4)=="#100")
    {
        is_gaming=1;
        std::cout<<"now start playing"<<"\n\r";
        p_deal_msg=&package::deal_msg_from_server_in_gaming;
        return;
    }
    std::cout<<"server :"<<msg<<"\r\n\r"; 

}

 void package::deal_msg_from_server_in_gaming(std::string &msg)
{  
    std::cout<<"------------------in gaming "<<std::endl;
    std::cout<<":):)"<<msg<<"\r\n\r";     
}
void package::deal_msg(std::string &msg)
{   
    (this->*p_deal_msg)(msg);
}