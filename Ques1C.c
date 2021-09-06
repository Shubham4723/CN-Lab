#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;
        char buffer[1024]={0};
	struct calc
        {
          int a;
          int b;
          char op;
        }c;
        
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	
	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
	{
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\nConnection Failed \n");
		return -1;
	}
        printf("\nEnter number 1:");
        scanf("%d",&c.a);
	
        printf("\nEnter number 2:");
        scanf("%d",&c.b);
        printf("\nEnter the operation:");
        scanf("%s",&c.op);
	send(sock , &c , sizeof(c) , 0 );
        //send(sock , &c.b , sizeof(c.b) , 0 );
        //send(sock , &c.op , sizeof(c.op) , 0 );
        printf("\nSent numbers.");
        int res;
	valread = read( sock ,&res, sizeof(res));
	printf("\nResult recieved from server is:%d",res);
	return 0;
}


