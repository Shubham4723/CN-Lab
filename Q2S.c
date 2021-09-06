// Server side implementation of UDP client-server model
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
int res=0;
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
len = sizeof(cliaddr); //len is value/resuslt
n = recvfrom(sockfd, &arr, sizeof(arr),
MSG_WAITALL, ( struct sockaddr *) &cliaddr,
&len);
int max=0;
for(int i=0;i<5;i++){
//printf("%s ",arr[i]);
int c=0;
for(int j=0;j<strlen(arr[i]);j++)
if(arr[i][j]==' ')
c++;
//printf("Number of words - %d",c);
if(c>max)
max=c;
}
max=max+1;
printf("Client : Received Strings Successfully.\n");
sendto(sockfd,&max, sizeof(int),
0, (const struct sockaddr *) &cliaddr,
len);
printf("Result sent.\n");
return 0;
}