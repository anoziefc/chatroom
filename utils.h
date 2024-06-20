#ifndef __UTILS__H__
#define __UTILS__H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

typedef struct acceptedSockets
{
	int fd;
	struct sockaddr_in socket_address;
	int error;
	bool acceptStatus;
} acceptedSockets;

int createTCPIPV4Socket(void);
struct sockaddr *createdTCPIPV4Address(char *ip, int PORT);
acceptedSockets *acceptIncomingConnections(int fd);
void *receiveIncomingData(void *fd);
void startConnectionsThread(int fd);
void acceptedConnectionsAndData(int fd);
void receiveIncomingDataOnDiffThread(int fd);

#endif
