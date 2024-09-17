#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#define BACKLOG 5

int esPrimo(int n){
    int contador = 0;
    int i = 1;
    while(i<=n){
        if(n % i == 0)contador++;
        if(contador > 2)return 0;
        i++;
    }
    return (contador == 2) ? 1 : 0; 
}
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
        int num;
        char response[5];
        printf("server waiting");
        client_len = sizeof(client_address);
        //accpet conexion
        client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);

        if(client_sockfd == -1)perror("accept");

        if(!fork()){
            read(client_sockfd,&num,sizeof(int));
            if(esPrimo(num)){
                sprintf(response,"yes");
            }
            else{
                sprintf(response,"no");
            }
            write(client_sockfd,response,sizeof(response));
            close(client_sockfd);
            exit(0);
        }else{
            close(client_sockfd);
        }
    }
}