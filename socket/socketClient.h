/***********************************************
 *  /detect/Debug/socket.h
 *
 *  Created on: 2017Äê11ÔÂ28ÈÕ
 *  Author: gift
 *
 ***********************************************/

#ifndef DEBUG_SOCKET_H_
#define DEBUG_SOCKET_H_

SOCKET startUDPSocketClient(struct in_addr locIp, unsigned short locPort);
int closeUDPSocketClient(SOCKET s);
int clientSendUDP(SOCKET s, struct in_addr desIp, unsigned short desPort, const char *pData, unsigned int dataLen);
int clientRecvUDP(SOCKET s, char *pRecvData, unsigned int maxRecvLen,
		struct in_addr *pRecvIp, unsigned short *pRecvPort, int blockTime_ms);

#endif /* DEBUG_SOCKET_H_ */
