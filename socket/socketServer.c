
/***********************************************
 *  /detect/socketServer.c
 *
 *  Created on: 2017年11月28日
 *  Author: gift
 *
 ***********************************************/

#ifndef SOCKETSERVER_C_
#define SOCKETSERVER_C_

#include <stdio.h>
#include <winsock2.h>
#include "typedef.h"
#include "socketUDP.h"

SOCKET startUDPSocketServer(struct in_addr serverIp, unsigned short listenPort) {

    WSADATA wsaData;
    WORD sockVersion = SOCKET_DEFAULT_VERSION;
    if(0 != WSAStartup(sockVersion, &wsaData)) {
    	printf("WSAStartup error !");
        return INVALID_SOCKET;
    }

    SOCKET serSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(INVALID_SOCKET == serSocket) {
        printf("socket error !");
        return INVALID_SOCKET;
    }

    //设置socket不报告UDP PORT_UNREACHABLE messages
    BOOL bNewBehavior = FALSE;
    DWORD dwBytesReturned = 0;
    WSAIoctl(serSocket, SIO_UDP_CONNRESET, &bNewBehavior, sizeof(bNewBehavior), NULL, 0, &dwBytesReturned, NULL, NULL);

    struct sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(listenPort);
    serAddr.sin_addr = serverIp;
    if(SOCKET_ERROR == bind(serSocket, (struct sockaddr *)&serAddr, sizeof(serAddr))) {
        printf("startUDPSocketServer : bind error !");
        closesocket(serSocket);
        return INVALID_SOCKET;
    }

    int value=65535;
    setsockopt(serSocket, SOL_SOCKET, SO_RCVBUF, (char*)&value, sizeof(value));
    setsockopt(serSocket, SOL_SOCKET, SO_SNDBUF, (char*)&value, sizeof(value));

    return serSocket;
}

int closeUDPSocketServer(SOCKET s) {

	int ret = closesocket(s);

    WSACleanup();

    printf("closeUDPSocketServer \r\n");

    return ret;
}

int serverSendUDP(SOCKET s, struct in_addr desIp, unsigned short desPort, const char *pData, unsigned int dataLen) {

	return sendUDP(s, desIp, desPort, pData, dataLen);
}

int serverRecvUDP(SOCKET s, char *pRecvData, unsigned int maxRecvLen,
		struct in_addr *pRecvIp, unsigned short *pRecvPort, int blockTime_ms) {

	return recvUDP(s, pRecvData, maxRecvLen, pRecvIp, pRecvPort, blockTime_ms);
}

#endif /* SOCKETSERVER_C_ */
