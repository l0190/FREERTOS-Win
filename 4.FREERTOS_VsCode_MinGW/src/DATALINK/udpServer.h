/***********************************
 * author: Jin Jia Bin
 * date: 2023-10-28
 ***********************************/
#ifndef __UDP_SERVER_H
#define __UDP_SERVER_H
#include <stdint.h>

#define SELF_ADDR_IP "127.0.0.1"
#define SELF_ADDR_PORT 14554

int udpServerInit(char *ip, int port);
void udpSendData(char *buff, int len);
void udp_rcv(char *buff, int *len);
#endif