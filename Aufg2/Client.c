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

	int sockfd, len, num=0;
	char numchar="0";
	ssize_t rc=NULL, receivedDatagram=NULL;
	struct sockaddr_in myaddr;
	char puffer[1500] = "Datagram No: ", recpuffer[1500];	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	fd_set rfds;
	FD_ZERO(&rfds);
	FD_SET(sockfd, &rfds);	
	struct timeval timeoutTime;
	timeoutTime.tv_sec = 2;
	timeoutTime.tv_usec = 0;
	


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
			
		len = sizeof(struct sockaddr_in);
		//snprintf(numstring,sizeof(numstring),"%d",num);
		//strcat(puffer, numstring);
		puffer[13] = numchar;
		
		num++;
		numchar = num + '0';
		rc = sendto(sockfd, puffer, sizeof(puffer), 0, (struct sockaddr*)&myaddr, len);	
				/* hier: warten auf input */	
		if (select(sockfd+1, &rfds, NULL, NULL, &timeoutTime)) {		
			receivedDatagram = recvfrom(sockfd, recpuffer, sizeof(recpuffer), 0, (struct sockaddr*)&myaddr, &len);
			printf("Sent:		%s\nReceived:	%s\n\n", puffer, recpuffer);	

		} else {
		int i;
		for (i = 0; i < 3; i++) {
			if (!select(sockfd+1, &rfds, NULL, NULL, &timeoutTime)){
			rc = sendto(sockfd, puffer, sizeof(puffer), 0, (struct sockaddr*)&myaddr, len);	
			printf("Resending, try number %d.\n", i);
			sleep(1);
		} else {
		break;
		}
		printf("Server not reachable.\n");
		exit(1);
	}
}
sleep(1);
}

close(sockfd);

exit(0);

}
