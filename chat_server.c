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
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
   if((sockfd = socket(AF_INET,SOCK_DGRAM,0)) < 0)
   {
      perror("socket creation failed");
      exit(EXIT_FAILURE);
   }
    memset(&servaddr,0,sizeof(servaddr));
    memset(&cliaddr,0,sizeof(cliaddr));

    //filling server information
   servaddr.sin_family=AF_INET;
   servaddr.sin_addr.s_addr=INADDR_ANY;
   servaddr.sin_port=htons(SERV_PORT);

   //bind the socket with the server address
   if(bind(sockfd, (const struct sockaddr*)&servaddr,
                 sizeof(servaddr))<0)
   {
      perror("bind failed");
      exit(EXIT_FAILURE);
   }

   struct sockaddr_in addrs[3];
   for(int i=0;i<3;++i)
   {
       memset(&addrs[i],0,sizeof(addrs[i]));
       addrs[i].sin_family= AF_INET;
       addrs[i].sin_addr.s_addr=INADDR_ANY;
       addrs[i].sin_port= htons(CL_PORT + i);
   }
   int len,n,from, to ,from_message;
   char buffer[MAXBUFF];

   while(1)
   {
       len=sizeof(cliaddr); //len is value/result
       n=recvfrom(sockfd, (char *)buffer,MAXBUFF,0, (struct sockaddr *)&cliaddr, &len);
       buffer[n] = '\0';
       from=ntohs(cliaddr.sin_port) - CL_PORT;
       from_message= buffer[0]-48;

       if(from != from_message)
       {
           //discard
           continue;
       }
       to = buffer[1]-48;
       if(from == to)
       {
           //discard
           continue;
       }
       if(to<0 || to>2)
       {
           //discard
           continue;
       }

       len=sizeof(addrs[to]);
       sendto(sockfd, (const char *)buffer, strlen(buffer),0, (const struct sockaddr *)&addrs[to],len);
       
   }

}
