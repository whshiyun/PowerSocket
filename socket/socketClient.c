#include <stdio.h>

/***********************************************
 *  /detect/socket.c
 *
 *  Created on: 2017年11月28日
 *  Author: gift
 *
 ***********************************************/

#include <winsock2.h>

#include "socketUDP.h"
#include "typedef.h"

SOCKET startUDPSocketClient(struct in_addr locIp, unsigned short locPort) {

    WORD socketVersion = SOCKET_DEFAULT_VERSION;
    WSADATA wsaData;
    if(0 != WSAStartup(socketVersion, &wsaData)) {
    	printf("WSAStartup error ! \r\n");
        return INVALID_SOCKET;
    }

    SOCKET cltSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(INVALID_SOCKET == cltSocket) {
        printf("socket error ! \r\n");
        return INVALID_SOCKET;
    }

    //设置socket不报告UDP PORT_UNREACHABLE messages
    BOOL bNewBehavior = FALSE;
    DWORD dwBytesReturned = 0;
    WSAIoctl(cltSocket, SIO_UDP_CONNRESET, &bNewBehavior, sizeof(bNewBehavior), NULL, 0, &dwBytesReturned, NULL, NULL);

    struct sockaddr_in locAddr;
    locAddr.sin_family = AF_INET;
    locAddr.sin_port = htons(locPort);
    locAddr.sin_addr = locIp;
    if(SOCKET_ERROR == bind(cltSocket, (struct sockaddr *)&locAddr, sizeof(locAddr))) {
        printf("startUDPSocketServer : bind error !");
        closesocket(cltSocket);
        return INVALID_SOCKET;
    }

    int value=65535;
    setsockopt(cltSocket, SOL_SOCKET, SO_RCVBUF, (char*)&value, sizeof(value));
    setsockopt(cltSocket, SOL_SOCKET, SO_SNDBUF, (char*)&value, sizeof(value));

    printf("startUDPSocketClient \r\n");

    return cltSocket;
}

int closeUDPSocketClient(SOCKET s) {

	int ret = closesocket(s);

    WSACleanup();

    printf("closeUDPSocketClient \r\n");

    return ret;
}

int clientSendUDP(SOCKET s, struct in_addr desIp, unsigned short desPort, const char *pData, unsigned int dataLen) {

    return sendUDP(s, desIp, desPort, pData, dataLen);
}

int clientRecvUDP(SOCKET s, char *pRecvData, unsigned int maxRecvLen,
		struct in_addr *pRecvIp, unsigned short *pRecvPort, int blockTime_ms) {

	return recvUDP(s, pRecvData, maxRecvLen, pRecvIp, pRecvPort, blockTime_ms);
}





