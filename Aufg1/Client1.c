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
	struct sockaddr_in myaddr, dest_addr, src_addr;
	char puffer[1500];	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockfd == -1) {
		perror("Socketzuordnung!");
		exit(1);
	}	

	memset(&myaddr, 0, sizeof(struct sockaddr_in));	
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(PORT);
	myaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	//rc = bind(sockfd, (struct sockaddr*) &myaddr, sizeof(struct sockaddr_in));
	if (rc == -1) {
		perror("Empfangsproblem");
		exit(1);
	}

	/* Hier müssen wir die Kommunikation programmieren */
	

	
		len = sizeof(struct sockaddr_in);
//		strcpy(puffer, "Hallo, Du weite Welt.");
		rc = sendto(sockfd, puffer, sizeof(puffer), 0, (struct sockaddr*)&myaddr, sizeof(struct sockaddr_in));
		
		rc = recvfrom(sockfd, puffer, sizeof(puffer), 0, (struct sockaddr*)&myaddr, sizeof(struct sockaddr_in));		
		printf("%s", puffer);	
	
	int i;
	for (i=0, i<100, i++) {
		myaddr.sin_addr.s_addr = inet_addr("141.64.89.66");
		sendto(sockfd, puffer, sizeof(puffer), 0, (struct sockaddr*)&myaddr, sizeof(struct sockaddr_in));
		}	
	close(sockfd);	

	exit(0);

}
