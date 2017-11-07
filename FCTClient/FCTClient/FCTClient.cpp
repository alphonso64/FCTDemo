// FCTClient.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "FCTClient.h"
#include "Winsock2.h"
#include "stdio.h"

#pragma comment(lib, "ws2_32.lib")

#define IMAGE_WIDTH   1292
#define IMAGE_HEIGHT  864


typedef struct detectresult
{
	unsigned int  id;
	unsigned int  grayscale;
	unsigned int  R;
	unsigned int  G;

	unsigned int  B;
	unsigned int  number;
	unsigned int  state;
	unsigned int  rev;

	unsigned int  similarity;

	unsigned int  picleft;

	unsigned int  pictop;

	unsigned int  picwidth;

	unsigned int  picheight;

	unsigned int  ppicture;

}DETECTRESULT;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}


// This is an example of an exported variable
FCTCLIENT_API int nFCTClient=0;

// This is an example of an exported function.
FCTCLIENT_API int fnFCTClient(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see FCTClient.h for the class definition
CFCTClient::CFCTClient()
{ 
	return; 
}

#pragma comment(lib, "Ws2_32")

#define PORT 15555

#define MAX_RECV_LEN (6 * 1024 * 1024)

#define BUF_SIZE (1024)
#define CMD_MAX  (256)

char recvBuf[MAX_RECV_LEN];
char sendBuf[BUF_SIZE];

char dataBuf[MAX_RECV_LEN];

char msg[BUF_SIZE];

int sockfd = -1;
char * addr = "127.0.0.1";

SOCKADDR_IN  server_addr;
WSADATA   ws;

char cmdbuf[CMD_MAX];

int isprocessfinished = 0;

int requestlen;

int g_numbytes = 0;

unsigned int paddr = 0;

DWORD threadid;

int recvdata(char * buf, int len);
int senddata(char * buf, int len);

DWORD WINAPI ThreadProc(LPVOID lpParam)
{

	int ret = -1;
	int receivelen = 0;
	memset(dataBuf, 0, sizeof(dataBuf));
	paddr = 0;
	
	isprocessfinished = 0;

	do
	{
		ret = recvdata(dataBuf + paddr, 0);
		if(-1 == ret)
		{
			isprocessfinished = -1;
			return -1;
		}
		paddr += ret;
	}while(paddr != *(unsigned int *)dataBuf);	
	isprocessfinished = 1;
	return 0;
}

FCTCLIENT_API int connect2host(void)
{
	int timeout = 300;

	WSAStartup(MAKEWORD(2, 2), &ws);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (SOCKET_ERROR == sockfd)
	{
		//printf("socket err.\n");
		return -1;
	}

	//if (-1 == setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout)) )
	//{
	//	return -2;
	//}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.S_un.S_addr = inet_addr(addr);

	if (-1 == connect(sockfd, (struct sockaddr *)(&server_addr), sizeof(struct sockaddr)))
	{
		//printf("connect err.\n");
		closesocket(sockfd);
		return -1;
	}
	return 0;
}

FCTCLIENT_API int start(int num, char * buf)
{
	char cmd[] = "S84C";
	isprocessfinished = 0;
	requestlen = num;
	paddr = 0;
	if (SOCKET_ERROR == sockfd)
	{
		//printf("not connected to server.\n");
		return -1;
	}

	if (num > 256)
	{
		//printf("so long.\n");
		return -2;
	}


	memcpy(sendBuf, cmd, 4);
	sendBuf[4] = num & 0xff;
	memcpy(sendBuf + 5, buf, num);

	if (-1 == send(sockfd, sendBuf, num + 5, 0))
	{
		//printf("send err. connection will be closed.\n");
		closesocket(sockfd);
		return -1;
	}
	
	CreateThread(NULL, 2048, ThreadProc, NULL, 0, &threadid);
	return 0;
}

FCTCLIENT_API int start_cam(int num, char * buf,int camIndex)
{
	
	isprocessfinished = 0;
	requestlen = num;
	paddr = 0;
	if (SOCKET_ERROR == sockfd)
	{
		//printf("not connected to server.\n");
		return -1;
	}

	if (num > 256)
	{
		//printf("so long.\n");
		return -2;
	}

	if(camIndex == 1)
	{
		char cmd[] = "S84C";
		memcpy(sendBuf, cmd, 4);
	}else if(camIndex == 2)
	{
		char cmd[] = "S84B";
		memcpy(sendBuf, cmd, 4);
	}else if(camIndex == 3)
	{
		char cmd[] = "S84A";
		memcpy(sendBuf, cmd, 4);
	}
	else{
		return -1;
	}

	
	sendBuf[4] = num & 0xff;
	memcpy(sendBuf + 5, buf, num);

	if (-1 == send(sockfd, sendBuf, num + 5, 0))
	{
		//printf("send err. connection will be closed.\n");
		closesocket(sockfd);
		return -1;
	}
	
	CreateThread(NULL, 2048, ThreadProc, NULL, 0, &threadid);
	return 0;
}

FCTCLIENT_API int selectimagesrc(int id)
{
	char cmd[] = "S84E";
	if (SOCKET_ERROR == sockfd)
	{
		return -1;
	}

	memcpy(sendBuf, cmd, 4);	
	memcpy(sendBuf + 4, (char *)&id, 4);

	if (-1 == send(sockfd, sendBuf, 8, 0))
	{
		closesocket(sockfd);
		return -1;
	}

	int ret = -1;
	memset(dataBuf, 0, sizeof(dataBuf));	
	ret = recvdata(dataBuf, 0);
	if(ret > 0)
	{
		ret = *(int *)(dataBuf);
	}
	return ret;
}

FCTCLIENT_API int changeimage(int len,char *path)
{
	char cmd[] = "S84F";
	if (SOCKET_ERROR == sockfd)
	{
		return -1;
	}

	memcpy(sendBuf, cmd, 4);
	memcpy(sendBuf + 4, (char *)&len, 4);
	memcpy(sendBuf + 8, path, len);

	if (-1 == send(sockfd, sendBuf, 8+len, 0))
	{
		closesocket(sockfd);
		return -1;
	}

	int ret = -1;
	memset(dataBuf, 0, sizeof(dataBuf));	
	ret = recvdata(dataBuf, 0);
	if(ret > 0)
	{
		ret = *(int *)(dataBuf);
	}
	return ret;
}

FCTCLIENT_API int loadpatternfile(int srccode,int len,char *path)
{
	char cmd[] = "S84D";
	if (SOCKET_ERROR == sockfd)
	{
		//printf("not connected to server.\n");
		return -1;
	}

	memcpy(sendBuf, cmd, 4);
	memcpy(sendBuf + 4, (char *)&srccode, 4);
	memcpy(sendBuf + 8, (char *)&len, 4);
	memcpy(sendBuf + 12, (char *)path, len);
	if (-1 == send(sockfd, sendBuf, 12+len, 0))
	{
		closesocket(sockfd);
		return -1;
	}

	int ret = -1;
	memset(dataBuf, 0, sizeof(dataBuf));	
	ret = recvdata(dataBuf, 0);
	if(ret > 0)
	{
		ret = *(int *)(dataBuf);
	}
	return ret;
}

FCTCLIENT_API int check()
{	
	return isprocessfinished;
}

int senddata(char * buf, int len)
{
	if (SOCKET_ERROR == sockfd)
	{
		//printf("not connected to server.\n");
	}

	if (len > 1024)
	{
		//printf("data_too_long.\n");
	}

	if (-1 == send(sockfd, buf, len, 0))
	{
		//printf("send err.\n");
		//closesocket(sockfd);
		return -1;
	}
	return 0;
}

int recvdata(char * buf, int len)
{
	int numbytes;
	numbytes = recv(sockfd, recvBuf, MAX_RECV_LEN, 0);
	if (-1 == numbytes)
	{
		return -1;
	}

	recvBuf[numbytes] = '\0';

	if(numbytes > 0)
	{
		memcpy(buf, recvBuf, numbytes);
		g_numbytes = numbytes;
	}
	
	return numbytes;
}

FCTCLIENT_API int getresult(int * result, int *pimg)
{
	int total_len;
	int head_len;
	int w ;
	int h;

    char * paddr = NULL;

	total_len = *(int *)dataBuf;
	w = *(int *)(dataBuf+8);
	h = *(int *)(dataBuf+12);

	head_len = total_len - w * h * 4;
    paddr = dataBuf + head_len;

	memcpy((char *)result, (char *)dataBuf, head_len);
    memcpy((char *)pimg, (char *)paddr, w * h * 4);

	return 0;
}

FCTCLIENT_API int getimagesize(int *w,int *h)
{
	*w = *(int *)(dataBuf+8);
	*h = *(int *)(dataBuf+12);
	return 0;
}
