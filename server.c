// <server.c>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <time.h>

#define PORT 2300

int main(int argc, char *argv[]) {
	/* For time intensive purposes*/
	time_t rawtime;
  	struct tm *timeinfo;

  	time (&rawtime );
  	timeinfo = localtime ( &rawtime );
  	printf("Current local time and date: %s", asctime(timeinfo) );

	/* Message to incoming connections. */
	char *msg = "Penguin...";

	struct sockaddr_in dest; // info about the machine connecting to us
	struct sockaddr_in serv; // info about our server
	int sock;		 // socket to listen for incoming conxns

	socklen_t socksize = sizeof(struct sockaddr_in);

	memset(&serv, 0, sizeof(serv)); // zero the struct before filling

	serv.sin_family = AF_INET;
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	serv.sin_port = htons(PORT);

	sock = socket(AF_INET, SOCK_STREAM, 0);

	/* bind serv information to sock */
	bind(sock, (struct sockaddr *)&serv, sizeof(struct sockaddr));

	/* start listening, allowing queue of 1 pending connection */
	listen(sock, 1);
	int con = accept(sock, (struct sockaddr *)&dest, &socksize);

	while (con) {

		printf("Incoming connection from: %s \n", inet_ntoa(dest.sin_addr));

		send(con, msg, strlen(msg), 0);

		close(con);

		con = accept(sock, (struct sockaddr *)&dest, &socksize);
	}
	close(sock);
	return EXIT_SUCCESS;
}
