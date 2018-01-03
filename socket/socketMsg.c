

/***********************************************
 *  /detect/socket/socketMsg.c
 *
 *  Created on: 2017Äê11ÔÂ28ÈÕ
 *  Author: gift
 *
 ***********************************************/

#include <stddef.h>
#include "socketMsg.h"


int mkSocketHead(char *pPkt, unsigned int msgType, unsigned int msgLen, int timeout) {

	if(NULL == pPkt)
		return -1;

	((P_SOCKET_MSG_HEAD)pPkt)->msgType = msgType;
	((P_SOCKET_MSG_HEAD)pPkt)->msgLen = msgLen;
	((P_SOCKET_MSG_HEAD)pPkt)->timeout = timeout;

	return sizeof(SOCKET_MSG_HEAD);
}
