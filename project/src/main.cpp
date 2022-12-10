#include "../inc/webserv.hpp"

#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

int main(int argc, char **argv, char **envp)
{
	(void)envp;
	(void)argc;
	(void)argv;

	HttpParser request;
	HttpParser response;

	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	fd_set active, readyRead, readyWrite;
	int max_fd = 0, new_fd = 0;

	if (server_socket == -1)
	{
		perror("socket");
		exit(1);
	}

	FD_ZERO(&active);

	max_fd = server_socket;
	FD_SET(server_socket, &active);

	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8080);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	// close server if already running
	int opt = 1;
	if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
	{
		perror("setsockopt");
		exit(1);
	}

	// bind server
	if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
	{
		perror("bind");
		exit(1);
	}

	// listen for connections on server socket
	if (listen(server_socket, 1024) == -1)
	{
		perror("listen");
		exit(1);
	}

	// loop forever to accept connections
	while (1)
	{
		readyRead = active;
		readyWrite = active;
		if (select(max_fd + 1, &readyRead, &readyWrite, NULL, NULL) == -1)
		{
			perror("select");
			exit(1);
		}

		// request
		if (FD_ISSET(server_socket, &readyRead))
		{
			struct sockaddr_in client_addr;
			socklen_t client_addr_len = sizeof(client_addr);
			new_fd = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
			if (new_fd == -1)
			{
				perror("accept");
				exit(1);
			}
			FD_SET(new_fd, &active);
			if (new_fd > max_fd)
				max_fd = new_fd;

			char buffer[1024];
			int bytes_read = read(new_fd, buffer, 1024);
			if (bytes_read == -1)
			{
				perror("read");
				exit(1);
			}
			buffer[bytes_read] = '\0';
			try {
				request.parse(buffer);
				std::cout << std::endl;
				std::cout << request << std::endl;
			} catch (HttpException &e) {
				std::cout << e.what() << std::endl;
			}
		}

		// response
		if (FD_ISSET(new_fd, &readyWrite)) {
			char *buffer = strdup("HTTP/1.1 200 OK\r");
			write(new_fd, buffer, buffer ? strlen(buffer) : 0);
			// print response
			try {
				response.parse(buffer);
				std::cout << response << std::endl;
			} catch (HttpException &e) {
				std::cout << e.what() << std::endl;
			}
			close(new_fd);
			FD_CLR(new_fd, &active);
		}

	}

	return (0);
}