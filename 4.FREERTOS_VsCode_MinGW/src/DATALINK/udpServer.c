/***********************************
 * author: Jin Jia Bin
 * date: 2023-10-28
 ***********************************/
#include "udpServer.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <assert.h>
#include <unistd.h>

static SOCKET Udp;
struct sockaddr_in serverAddr; //服务器端地址
struct sockaddr_in selfAddr; //自己地址
int udpServerInit(char *ip, int port){
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("Failed to load WinSock.\n"); //WinSock 初始化错误
        return -1;
    }
    serverAddr.sin_family = AF_INET;                                //初始化服务器地址信息
    serverAddr.sin_port = htons(port);                     //端口转换为网络字节序
    serverAddr.sin_addr.s_addr = inet_addr(ip);                 //IP 地址转换为网络字节序


    selfAddr.sin_family = AF_INET;
    selfAddr.sin_port = htons(14560);
    selfAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    Udp = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //创建UDP套接字
    if (Udp == INVALID_SOCKET)
    {
        printf("socket() Failed: %d\n", WSAGetLastError());
        return -1;
    }
    if (bind(Udp, (LPSOCKADDR)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        printf("error bind port error\n");
        return 0;
    }
    printf("udp init ok\n");
}

/**
 * 发送
 */
void udpSendData(char *buff, int len){
    sendto(Udp, buff, len, 0, (SOCKADDR *)&selfAddr, sizeof(selfAddr));
}

/**
 * 接受
 */
void udp_rcv(char *buff, int *len)
{
    int fromLen = sizeof(struct sockaddr_in);
    *len = recvfrom(Udp, buff, 256, 0, (SOCKADDR *)&selfAddr, &fromLen);
}

/**
 * 关闭
 */
int close_udp()
{
    closesocket(Udp); //关闭 socket
    WSACleanup();
}