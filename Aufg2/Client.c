#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PORT 4030

int main() {

	int sockfd, len, num=0, status = 0, i=0;
	char numchar="0";
	ssize_t rc=NULL, receivedDatagram=NULL;
	struct sockaddr_in myaddr;
	char puffer[1500] = "Datagram No: ", recpuffer[1500];	

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	fd_set rfds, CPrfds;	
	FD_ZERO(&rfds);
	FD_SET(sockfd, &rfds);	
	struct timeval timeoutTime;
	


	if (sockfd == -1) {
		perror("Socketzuordnung!");
		exit(1);
	}	

	memset(&myaddr, 0, sizeof(struct sockaddr_in));	
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(PORT);
	//rc = bind(sockfd, (struct sockaddr*) &myaddr, sizeof(struct sockaddr_in));
	if (rc == -1) {
		perror("Empfangsproblem");
		exit(1);
	}

	/* Hier müssen wir die Kommunikation programmieren */

	/* @TODO	besseres Hochzaehlen,
			Timeout
	*/

	while(1) {
		timeoutTime.tv_sec = 2;
		timeoutTime.tv_usec = 0;
		CPrfds = rfds;
	
		len = sizeof(struct sockaddr_in);
		puffer[13] = numchar;
		
	
		rc = sendto(sockfd, puffer, sizeof(puffer), 0, (struct sockaddr*)&myaddr, len);	
				
		status = select(sockfd+1, &CPrfds, NULL, NULL, &timeoutTime);
				
		
		if(status>0) {
				
			receivedDatagram = recvfrom(sockfd, recpuffer, sizeof(recpuffer), 0, (struct sockaddr*)&myaddr, &len);
			printf("Sent:		%s\nReceived:	%s\n\n", puffer, recpuffer);	
			if (num < 10) {	
				num++;
			} else {
				num = 0;
			}
	
			numchar = num + '0';
		
			
		} else {
		// server can't be reached
			if (i < 3) {
				sleep(1);
				printf("Resending.\n");
				i++;
				continue;
			} else {
			printf("Server can't be reached.\n");
			exit(EXIT_FAILURE);
			}		
			
		}

	
				
		
	

		}
	
	


receivedDatagram = NULL;
close(sockfd);

exit(0);

}
