#include "utils.h"

int createTCPIPV4Socket(void)
{
	int client_socket = socket(AF_INET, SOCK_STREAM, 0);

	if (client_socket < 0)
	{
		perror("failed to create socket");
		exit(EXIT_FAILURE);
	}

	return (client_socket);
}

struct sockaddr *createdTCPIPV4Address(char *ip, int PORT)
{
	struct sockaddr_in *address;

	address = malloc(sizeof(struct sockaddr_in));

	address->sin_family = AF_INET;
	address->sin_port = htons(PORT);
	if (ip == NULL)
		address->sin_addr.s_addr = INADDR_ANY;
	else
		inet_pton(AF_INET, ip, &address->sin_addr.s_addr);

	return ((struct sockaddr *) address);
}

acceptedSockets *acceptIncomingConnections(int fd)
{
	acceptedSockets *acceptedSocket;
	int client_socket_fd;
	struct sockaddr_in client_address;
	unsigned int client_address_size = sizeof(struct sockaddr_in);

	client_socket_fd = accept(fd, (struct sockaddr *) &client_address,
								&client_address_size);

	acceptedSocket = malloc(sizeof(acceptedSockets));
	acceptedSocket->fd = client_socket_fd;
	acceptedSocket->socket_address = client_address;
	acceptedSocket->acceptStatus = client_socket_fd > 0;

	if (!acceptedSocket->acceptStatus)
		acceptedSocket->error = client_socket_fd;

	return (acceptedSocket);
}

void *receiveIncomingData(void *__fd)
{
	int fd = *(int *)__fd;
	char buffer[2048];
	ssize_t amount_received;

	while (true)
	{
		amount_received = recv(fd, buffer, 1024, 0);
		if (amount_received > 0)
		{
			buffer[amount_received] = 0;
			printf("%s", buffer);
		}
		else
			break;
	}
	close(fd);

	return NULL;
}

void acceptedConnectionsAndData(int fd)
{
	acceptedSockets *incomingConn;
	while (true)
	{
		incomingConn = acceptIncomingConnections(fd);
		receiveIncomingDataOnDiffThread(incomingConn->fd);
	}
	free(incomingConn);
}

void receiveIncomingDataOnDiffThread(int fd)
{
	pthread_t id;

	pthread_create(&id, NULL, receiveIncomingData, &fd);
}

void startConnectionsThread(int fd)
{
	acceptedSockets *incomingConn;
	while (true)
	{
		incomingConn = acceptIncomingConnections(fd);
		receiveIncomingDataOnDiffThread(incomingConn->fd);
	}

}
