

#include <stdio.h>
#include <winsock2.h> 

#pragma comment(lib, "ws2_32") /* WinSock ʹ�õĿ⺯��	*/

#define ECHO_DEF_PORT     7 /* ���ӵ�ȱʡ�˿� */
#define ECHO_BUF_SIZE   256 /* �������Ĵ�С	  */

int main()
{
    WSADATA wsa_data;
    SOCKET echo_soc = 0;      /* socket ��� */
    struct sockaddr_in serv_addr;   /* ��������ַ */
    unsigned short port = ECHO_DEF_PORT;
    int result = 0, send_len = 0;
    char *test_data = "Hello World!", recv_buf[ECHO_BUF_SIZE];
    printf("run");
	const char *Server_Ip = "127.0.0.1";
	const port = 27;
    WSAStartup(MAKEWORD(2,0), &wsa_data);/* ��ʼ�� WinSock��Դ */
    send_len = strlen(test_data);

    /* ��������ַ */
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = inet_addr(Server_Ip);

    if (serv_addr.sin_addr.s_addr == INADDR_NONE)
    {
        printf("[ECHO] invalid address\n");
        return -1;
    };

    echo_soc = socket(AF_INET, SOCK_STREAM, 0); /* ���� socket */
    result = connect(echo_soc, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    if (result == 0) /* ���ӳɹ� */
    {
        result = send(echo_soc, test_data, send_len, 0);
        result = recv(echo_soc, recv_buf, ECHO_BUF_SIZE, 0);
    }

    if (result > 0)
    {
        recv_buf[result] = 0;
        printf("[Echo Client] receives: \"%s\"\r\n", recv_buf);
    }
    else
        printf("[Echo Client] error : %d.\r\n", WSAGetLastError());

    closesocket(echo_soc);
    WSACleanup();
	int a;

	scanf("%d", &a);
    return 0;
}
