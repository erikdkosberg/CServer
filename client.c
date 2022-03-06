// <client.c>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <errno.h>

#define MAX_LEN 500
#define PORT	2300

int main(int argc, char *argv[]) {

	char buffer[MAX_LEN + 1]; //+1 for term null
	int len, sock;
	struct sockaddr_in dest;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	memset(&dest, 0, sizeof(dest));			// zero the struct
	dest.sin_family = AF_INET;
	dest.sin_addr.s_addr = htonl(INADDR_LOOPBACK);  // dest ip - local host
	dest.sin_port = htons(PORT);			// dest port number

	connect(sock,(struct sockaddr *)&dest, sizeof(struct sockaddr_in));

	len = recv(sock, buffer, MAX_LEN, 0);

	// Null term the received data
	buffer[len] = '\0';
	printf("Received %s (%d bytes). \n", buffer, len);

	close(sock);
	return EXIT_SUCCESS;
}
