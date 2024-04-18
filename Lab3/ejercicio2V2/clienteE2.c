#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
    int socket_fd;
    int address_len;
    struct sockaddr_in address;

    socket_fd = socket(AF_INET,SOCK_STREAM,0);
    if(socket_fd == -1){
        printf("No se realizo el socket");
        exit(0);
    }


    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9734);
    address_len = sizeof(address);
    
    if(connect(socket_fd,(struct sockaddr *)&address,address_len) == -1){
        printf("No se realizo la conexion");
        exit(0);
    }

    int num = atoi(argv[1]);
    write(socket_fd,&num,sizeof(num));
    close(socket_fd);
    exit(0);
}