#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080

int main(int argc, char const *argv[])
{
	int sock = 0,valread;
    
	struct sockaddr_in serv_addr;
	char sen[1024];
	printf("enter the sentance\n");
    fgets(sen, 1024, stdin);
	char res[1024];
    
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
	send(sock , sen , strlen(sen) , 0 );
	printf("Sentence sent\n");
	valread = read( sock , &res, sizeof(res));
	printf("The sentence without the vowels is %s and my roll number is 1928320",res);
	return 0;
}


