// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	8000
#define MAXLINE 1024

// Driver code
struct student{
	int id;
	char name[10];
};
int main() {
	int sockfd;
	struct student s1[3];
	struct sockaddr_in	 servaddr;

	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;
	
	int n, len;
	for(int i = 0; i<3; i++){
	scanf("%d", &s1[i].id);
	scanf("%s", s1[i].name);
}
	
	sendto(sockfd, s1, sizeof(struct student)*3,
		0, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
	printf("Structure sent.\n");
		
	n = recvfrom(sockfd, s1, sizeof(struct student)*3,
				MSG_WAITALL, (struct sockaddr *) &servaddr,
				&len);
	for(int i = 0; i<3; i++){
	printf("Server : %d, %s\n", s1[i].id, s1[i].name);
	}
	close(sockfd);
	return 0;
}

