// Server side implementation of UDP client-server model
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
	struct sockaddr_in servaddr, cliaddr;
	struct student s1[3];
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
	
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
	
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,
			sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	
	int len, n;
	int rem = 0, rev[3];

	len = sizeof(cliaddr);
 
	n = recvfrom(sockfd, s1, sizeof(struct student)*3,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
	
	for(int i = 0; i < 3; i++){
		printf("Client : %d, %s\n", s1[i].id, s1[i].name);
}
      	for(int j = 0; j < 3; j++){
		while( s1[j].id != 0){
			rem = s1[j].id % 10;
			rev[j] = rev[j] * 10 + rem;
			s1[j].id /= 10;
			}
}
	for(int k = 0; k < 3; k++){
		s1[k].id = rev[k];
	}

	sendto(sockfd, s1, sizeof(struct student)*3,
		0, (const struct sockaddr *) &cliaddr,
			len);
	printf("Modified structure sent!\n");
	
	return 0;
}

