// Server side implementation of UDP client-server model
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
	char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;
	
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
	
	int len, n, result, r, c;
	int a, i;
	len = sizeof(cliaddr); //len is value/resuslt 
    
    
	n = recvfrom(sockfd, &a, sizeof(int),
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
				
/*	n = recvfrom(sockfd, &b, sizeof(int),
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);   */
							
	for(i=1;i<=a;i++)		
	 {
	 	r = a % i;
	 	
	 	 if(r==0)
	 	   c++;
	 	r = 0;
	 }
	 
	 if(c==2)
	   result = 1;
	   
	else
	   result = 0;
	buffer[n] = '\0';
	printf("Client : %d\n", result);
	sendto(sockfd, &a, sizeof(int),
		0, (const struct sockaddr *) &cliaddr,
			len);
			
	//printf("Hello message sent.\n");
	
	return 0;
}

