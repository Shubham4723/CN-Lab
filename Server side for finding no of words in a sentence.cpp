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
	
	int len, n;
	char line[100];
	len = sizeof(cliaddr); //len is value/resuslt 
    
    
	n = recvfrom(sockfd,line, sizeof(char)*100,
				MSG_WAITALL, ( struct sockaddr *) &cliaddr,
				&len);
						
	int wordCount = 0;  
        
        for(int i = 0; i < strlen(line)-1; i++) 
	{  
        	if(line[i] == ' ' && (line[i+1]) && (i > 0)) 
			{  
        		    wordCount++;  
        		}  
        }    
        wordCount++;  		
	
	buffer[n] = '\0';
	printf("Client : %d\n", wordCount);
	sendto(sockfd, &wordCount, sizeof(int),
		0, (const struct sockaddr *) &cliaddr,
			len);
			
	//printf("Hello message sent.\n");
	
	return 0;
}

