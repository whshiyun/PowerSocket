/***********************************************
 *  /detect/socketUDP.h
 *
 *  Created on: 2017��11��28��
 *  Author: gift
 *
 ***********************************************/

#ifndef SOCKETUDP_H_
#define SOCKETUDP_H_

int sendUDP(SOCKET s, struct in_addr desIp, unsigned short desPort, const char *pData, unsigned int dataLen);
int recvUDP(SOCKET s, char *pRecvData, unsigned int maxRecvLen,
		struct in_addr *pRecvIp, unsigned short *pRecvPort, int blockTime_ms);

#endif /* SOCKETUDP_H_ */
