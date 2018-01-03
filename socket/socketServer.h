/***********************************************
 *  /detect/socketServer.h
 *
 *  Created on: 2017Äê11ÔÂ28ÈÕ
 *  Author: gift
 *
 ***********************************************/

#ifndef SOCKETSERVER_H_
#define SOCKETSERVER_H_

SOCKET startUDPSocketServer(struct in_addr serverIp, unsigned short listenPort);
int closeUDPSocketServer(SOCKET s);
int serverSendUDP(SOCKET s, struct in_addr desIp, unsigned short desPort, const char *pData, unsigned int dataLen);
int serverRecvUDP(SOCKET s, char *pRecvData, unsigned int maxRecvLen,
		struct in_addr *pRecvIp, unsigned short *pRecvPort, int blockTime_ms);

#endif /* SOCKETSERVER_H_ */
