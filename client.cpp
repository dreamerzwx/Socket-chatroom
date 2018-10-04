#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include<process.h>
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
#define MAXNUM 2000
unsigned int threadID;
HANDLE handle;
SOCKET sock;

unsigned int __stdcall fun(PVOID PM ) 
{char buf[MAXNUM];

while(1)
{
    int cc = recv(sock, buf, MAXNUM, 0);   //cc为接收的字符数
    if(cc == SOCKET_ERROR|| cc == 0)
    {
        printf("Error: %d.----",GetLastError());
        printf("服务器已断开\n");
        CloseHandle(handle);
        closesocket(sock);
        break;
    }
    else if(cc > 0) 
    {
        printf("%s",buf);
    }     
}
    return 0;
}

int main(){
    //初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
 
    //创建套接字
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
 
    //向服务器发起请求
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(100);
    connect(sock, (sockaddr*)&sockAddr,sizeof(sockaddr));
	printf("\t\t您已进入聊天室\n");
	handle=(HANDLE)_beginthreadex(NULL,0,fun,NULL,0,&threadID);

	while(1)
	{
		char buf1[MAXNUM];
		scanf("%s",buf1);
		send(sock,buf1, sizeof(buf1), 0);
	printf(" 发送成功\n");
	}
    //关闭套接字
    closesocket(sock); 
    //终止使用 DLL
    WSACleanup();
    system("pause");
    return 0;
}
