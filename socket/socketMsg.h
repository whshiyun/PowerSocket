/***********************************************
 *  /detect/socket/socketMsg.h
 *
 *  Created on: 2017��11��28��
 *  Author: gift
 *
 ***********************************************/

#ifndef SOCKET_SOCKETMSG_H_
#define SOCKET_SOCKETMSG_H_

typedef struct __socket_msg_head {
	unsigned int msgType;
	unsigned int msgLen;//msgLen����ʵ���������ֶγ���
	int timeout;
}__attribute__ ((gcc_struct, packed)) SOCKET_MSG_HEAD, *P_SOCKET_MSG_HEAD;

int mkSocketHead(char *pPkt, unsigned int msgType, unsigned int msgLen, int timeout);

#endif /* SOCKET_SOCKETMSG_H_ */
