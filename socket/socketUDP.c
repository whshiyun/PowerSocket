#include <stdio.h>

/***********************************************
 *  /detect/Debug/socketUDP.c
 *
 *  Created on: 2017年11月28日
 *  Author: gift
 *
 ***********************************************/

#include <winsock2.h>

int sendUDP(SOCKET s, struct in_addr desIp, unsigned short desPort, const char *pData, unsigned int dataLen) {

	if((NULL == pData) || (INVALID_SOCKET == s))
		return SOCKET_ERROR;

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(desPort);
//    sin.sin_addr.S_un.S_addr = desIp;//inet_addr(pDesIp);
    sin.sin_addr = desIp;
    int len = sizeof(sin);

    return sendto(s, pData, dataLen, 0, (struct sockaddr *)&sin, len);
}

int recvUDP(SOCKET s, char *pRecvData, unsigned int maxRecvLen,
		struct in_addr *pRecvIp, unsigned short *pRecvPort, int blockTime_ms) {

	if((NULL == pRecvData) || (INVALID_SOCKET == s))
		return SOCKET_ERROR;

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    int len = sizeof(sin);

    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(s, &readfds);

    struct timeval *pTv = NULL;
    if(blockTime_ms >= 0) {
    	pTv = (struct timeval *)malloc(sizeof(struct timeval));
    	pTv->tv_sec = blockTime_ms / 1000;
    	pTv->tv_usec = blockTime_ms % 1000;
    }

    if(SOCKET_ERROR == select(0, &readfds, NULL, NULL, pTv)) {
    	char str[10] = { 0 };
    	itoa(WSAGetLastError(),str,10);
    	printf("recvUDP : select error code = "); printf(str); printf("\r\n");
    }

    if(NULL != pTv)
    	free(pTv);

    if(FD_ISSET(s, &readfds)) {
    	int ret = recvfrom(s, pRecvData, maxRecvLen, 0, (struct sockaddr *)&sin, &len);
    	if(ret > 0)	{
    		if(NULL != pRecvIp)
    			*pRecvIp = sin.sin_addr;
    		if(NULL != pRecvPort)
    			*pRecvPort = ntohs(sin.sin_port);
    		return ret;
    	} else {
        	char str[10] = { 0 };
        	itoa(WSAGetLastError(),str,10);
        	printf("recvUDP : recvfrom error code = "); printf(str); printf("\r\n");
        }
    }

    //如果FD_ISSET(s, &readfds)返回false，说明没有接收到数据
    //数据接收长度需返回0
    return 0;
}
