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

	int sockfd;
	struct sockaddr_in myaddr, src_addr;
	
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	if (sockfd == -1) {
		perror("Socketzuordnung!");
		exit(1);
	}	

	memset(&myaddr, 0, sizeof(struct sockaddr_in));	
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(PORT);
	bind(sockfd, (struct sockaddr *) &myaddr, sizeof(struct sockaddr_in));

	while(1);

	exit(0);

}
