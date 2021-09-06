#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 8080
int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    struct calc
    {
      int a;
      int b;
      char op;
    }c;
    
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                             (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    valread = read(new_socket, &c, sizeof(c));
    //valread = read(new_socket, &c.b, sizeof(c.b));
    //valread = read(new_socket, &c.op, sizeof(c.op));
    printf("\nNumbers read.");
    int res;
    switch(c.op)
    {
      case '+' : res=c.a+c.b;
                 break;
      case '-' : res=c.a+c.b;
                 break;
      case '*' : res=c.a+c.b;
                 break;
      case '/' : res=c.a+c.b;
                 break;
      default  : printf("Wrong imput operator!");
                 break;
    }
    send(new_socket,&res, sizeof(res), 0);
    printf("Result sent.\n");
    close(new_socket); // closes this particular connection
    close(server_fd); // server cannot accept any more connections
    return 0;
}

