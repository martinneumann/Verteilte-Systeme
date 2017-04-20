#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PORT 4030

int main() {

	int sockfd, sfd, len;
	ssize_t rc=0;
	struct sockaddr_in myaddr, src_addr;
	char puffer[1500];	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockfd == -1) {
		perror("Socketzuordnung!");
		exit(1);
	}	

	memset(&myaddr, 0, sizeof(struct sockaddr_in));	
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(PORT);
	rc = bind(sockfd, (struct sockaddr*) &myaddr, sizeof(struct sockaddr_in));
	if (rc == -1) {
		perror("Empfangsproblem");
		exit(1);
	}

	/* Hier müssen wir die Kommunikation programmieren */
	
	while(1) {
	
		len = sizeof(struct sockaddr_in);
		rc = recvfrom(sockfd, puffer, sizeof(puffer), 0, (struct sockaddr*)&myaddr, &len);	
		
		while(1) {
		strcpy(puffer,"HALLO JOSEF\n");	
		sendto(sockfd, puffer, sizeof(puffer), 0, (struct sockaddr*)&myaddr, len);
	}
	}

	

	exit(0);

}
