#include "utils.h"

int main(void)
{
	int server_socket_fd = createTCPIPV4Socket();
	char *ip = NULL;
	int PORT = 2000;
	struct sockaddr *address = createdTCPIPV4Address(ip, PORT);
	int bind_server_network = bind(server_socket_fd, address, sizeof(*address));

	if (bind_server_network == 0)
		printf("Server successfully bound\n");
	listen(server_socket_fd, 10);
	startConnectionsThread(server_socket_fd);

	free(address);
	shutdown(server_socket_fd, SHUT_RDWR);

	return (0);
}
