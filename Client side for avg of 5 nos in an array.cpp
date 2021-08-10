// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT	 6000
#define MAXLINE 1024

// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from client";
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
	
	int a[5];
        for(int i=0; i<5; i++)
            {
	      scanf("%d",&a[i]);
            }
	sendto(sockfd,a, sizeof(int)*5,
		0, (const struct sockaddr *) &servaddr,
			sizeof(servaddr));
		
			
	//printf("Hello message sent.\n");
	
	len = sizeof(servaddr);
	float result;
		
	n = recvfrom(sockfd, &result, sizeof(int),
				MSG_WAITALL, (struct sockaddr *) &servaddr,
				&len);
	buffer[n] = '\0';

	close(sockfd);
	return 0;
}

