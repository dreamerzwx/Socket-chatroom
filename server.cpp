#include<stdio.h>
#include<winsock2.h>
#include<process.h>
#pragma comment(lib,"ws2_32.lib")
#define MAXNUM 2000
#define MAXCON 5
SOCKET sock[MAXCON]={NULL},sSock,cSock;
sockaddr cAddr;
sockaddr_in  sockAddr;
int nsize,num=-1,cc;
HANDLE handle[MAXCON];
unsigned int threadId;

unsigned int _stdcall fun(PVOID pM)
{
	char buf1[MAXNUM],buf2[MAXNUM],buf3[MAXNUM],buf4[MAXNUM];
	sock[num]=cSock;
	SOCKET s=cSock;
	unsigned int threadid=threadId;
	sprintf(buf4,"'-----我的线程号:%d-----\n",threadid);
//	printf("'-----我的线程号:%d-----\n",threadid);
	send(s,buf4,sizeof(buf4),0);
	sprintf(buf1,"'-----系统:用户%d进入聊天室-----\n",threadId);
	printf("'-----系统:用户%d进入聊天室-----\n",threadId);
	for(int i=0;i<=num;i++)
	{
		if(sock[i]!=s&&sock[i]!=NULL)
	send(sock[i],buf1,sizeof(buf1),0);
	}
go:cc=recv(s,buf2,MAXNUM,0);
   if(cc==SOCKET_ERROR||cc==0)
   {
	   sprintf(buf2,"-----用户%d离开聊天室-----\n",threadid);
	   printf("-----用户%d离开聊天室-----\n",threadid);
	   for(int i=0;i<=num;i++)
	{
	if(sock[i]!=s&&sock[i]!=NULL)
	send(sock[i],buf2,sizeof(buf2),0);
	}
   }
   else if(cc>0)
   {
	   sprintf(buf3,"用户%d:%s\n",threadid,buf2);
	   printf("用户%d:%s\n",threadid,buf2);
	    for(int i=0;i<=num;i++)
	{
		if(sock[i]!=s&&sock[i]!=NULL)
	send(sock[i],buf3,sizeof(buf3),0);
	}
		goto go;
   }

 (void) closesocket(s);
    
        return 0;
}

int main()
{
	WSADATA wdata;
	WSAStartup(MAKEWORD(2,2),&wdata);
	sSock =socket(AF_INET,SOCK_STREAM,0);
	memset(&sockAddr,0,sizeof(sockAddr));
	sockAddr.sin_family=AF_INET;
	sockAddr.sin_addr.s_addr=INADDR_ANY;
	sockAddr.sin_port=htons(100);
	bind(sSock,(sockaddr*)&sockAddr,sizeof(sockaddr));
	listen(sSock,MAXCON);
	while(1)
	{
	nsize=sizeof(sockaddr);
	cSock=accept(sSock,(sockaddr*)&cAddr,&nsize);
	num++;
	handle[num]=(HANDLE)_beginthreadex(NULL,0,fun,NULL,0,&threadId);
	}
    closesocket(sSock); 
	WSACleanup(); 
	return 0;
}