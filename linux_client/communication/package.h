#pragma once
#include <iostream>
#include "../chess/chess.h"
#include "../chess/global.h"
#include "../chess/checkerboard.h"
#include "IKTCP_CLIENT.h"
class package
{
public:
    typedef bool user_status;
    user_status is_gaming;
    package(IKTCP_CLIENT &main_cln);
    void deal_msg_from_server(std::string &msg); //将服务器的标识符转换为客户能够显示的语言
    void deal_msg_from_server_in_gaming(std::string &msg);
    void (package::*p_deal_msg)(std::string &);
    void deal_msg(std::string &msg);
    void deal_msg_from_client_in_gaming();
private:
    const static char *split_symbol;
    checkerboard *main_checkerboard;
    IKTCP_CLIENT *main_cln;
};