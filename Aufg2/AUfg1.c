#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
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

	exit(0);

}
