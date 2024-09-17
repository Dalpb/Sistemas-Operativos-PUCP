#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#define BACKLOG 5
int main(){
    int server_sockfd,client_sockfd;
    int server_len,client_len;
    struct sockaddr_in server_address,client_address;
//socket protocolo internet v4
    server_sockfd = socket(AF_INET,SOCK_STREAM,0);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9734); //puerto
    server_len = sizeof(server_address);

    bind(server_sockfd,(struct sockaddr *)&server_address,server_len);

    if(listen(server_sockfd,BACKLOG) == -1)
        perror("listen");    

    while(1){
        char ch;
        printf("server waiting");
        client_len = sizeof(client_address);
        //accpet conexion
        client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);

        if(client_sockfd == -1)perror("accept");

        read(client_sockfd,&ch,1); //espero hasta que envie algo y lo leo lo enviado por el cliente
        ch++;
        write(client_sockfd,&ch,1); //envio algo al cliente
        close(client_sockfd); //cierra conexion con el cliente aceptado
    }
}