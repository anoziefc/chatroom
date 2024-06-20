#include "utils.h"

int main(void)
{
	int client_socket_fd = createTCPIPV4Socket();
	char *ip = "0.0.0.0";
	int PORT = 2000;
	int client_connection;
	struct sockaddr *address = createdTCPIPV4Address(ip, PORT);
	char *line = NULL;
	ssize_t char_count = 0;
	size_t line_size = 0;
	ssize_t amount_sent = 0;

	client_connection = connect(client_socket_fd, address, sizeof(*address));

	if (client_connection == 0)
		printf("Connection was successful\n");
	else
		printf("Connection was not successful\n");

	while (true)
	{
		char_count = getline(&line, &line_size, stdin);

		if (char_count > 0)
		{
			if (strcmp(line, "exit\n") == 0)
				break;
			amount_sent = send(client_socket_fd, line, strlen(line), 0);
			if (amount_sent < 0)
			{
				perror("sending failed!");
				exit(EXIT_FAILURE);
			}
		}
	}
	free(address);
	free(line);

	return (0);
}
