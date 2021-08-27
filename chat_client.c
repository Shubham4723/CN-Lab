#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define CL_PORT 8080
#define SERV_PORT 9090
#define MAXBUFF 1024

int main(int argc, char **argv)
{
   int client_number, sockfd;
   client_number = (*argv[1])-48;

   struct sockaddr_in servaddr, cliaddr;

   if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0)
   {
      perror("socket creation failed");
      exit(EXIT_FAILURE);
   }

   memset(&servaddr,0,sizeof(servaddr));
   memset(&cliaddr,0,sizeof(cliaddr));

   //Filling own information
   cliaddr.sin_family=AF_INET;
   cliaddr.sin_addr.s_addr=INADDR_ANY;
   cliaddr.sin_port=htons(CL_PORT + client_number);

   //Bind the socket with the server address
   if(bind(sockfd, (const struct sockaddr*)&cliaddr,
                 sizeof(cliaddr))<0)
   {
      perror("bind failed");
      exit(EXIT_FAILURE);
   }

   //filling server information
   servaddr.sin_family=AF_INET;
   servaddr.sin_addr.s_addr=INADDR_ANY;
   servaddr.sin_port=htons(SERV_PORT);
    
   int len,n, from, to, from_message;

   while(1)
   {
       printf("Type r for receive mode or s for send mode:");
       char response;
       scanf("%c", &response);

       if(response=='s')
       {
         char buffer[MAXBUFF];
         printf("Enter a message in the correct format:");
         scanf("%s", buffer);

         //send to server
         len=sizeof(servaddr);
         sendto(sockfd, (const char *)buffer, strlen(buffer),0, (const struct sockaddr *)&servaddr, len);
       }

       if(response=='r')
       {
           char buffer[MAXBUFF];
           len=sizeof(servaddr);
           n=recvfrom(sockfd, (char *)buffer,MAXBUFF,0, (struct sockaddr *)&servaddr, &len);
           buffer[n]= '\0';

           printf("%s\n", buffer);
       }
   }
}
