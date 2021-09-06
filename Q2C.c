// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define PORT 8080
#define MAXLINE 1024
// Driver code
int main() {
int sockfd;
char arr[5][100];
printf("Enter the sentences - \n");
for(int i=0;i<5;i++)
fgets(arr[i], 100, stdin);
struct sockaddr_in servaddr;
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
sendto(sockfd, &arr, sizeof(arr),
0, (const struct sockaddr *) &servaddr,
sizeof(servaddr));
printf("Client sent the array.\n");
int result;
len=sizeof(servaddr);
n = recvfrom(sockfd, &result, sizeof(int),
MSG_WAITALL, (struct sockaddr *) &servaddr,
&len);
printf("Server : Result - %d words\n", result);
close(sockfd);
return 0;
}