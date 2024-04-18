#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
int esPrimo(int num){
    int div =0 ;
    for(int i=1; i<=num;i++){
        if(num%i == 0)div++;
    }
    return div==2 ? 1: 0;
}
int main(){

    //creo los archivos de comunicacion
    int server_sockfd,client_sockfd;
    //tamaños de direcciones
    socklen_t server_len,client_len;

    //direcciones
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    server_sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(server_sockfd == -1)perror("socket");

    //configuramos address socket
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr =htonl(INADDR_ANY);
    server_address.sin_port = htons(9734);
    server_len = sizeof(server_address);

    //confirmo quiero una conexion
    int binSucces=bind(server_sockfd,(struct sockaddr *)&server_address,server_len);
    if(binSucces== -1)perror("bind");

    int listenSucces = listen(server_sockfd,5);
    if(listenSucces == -1)perror("listen");

    for(;;){            
        printf("Server waiting\n");
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);
        if(client_sockfd == -1){
            perror("accept");
        }
        int num;
        read(client_sockfd,&num,sizeof(num));
        if(esPrimo(num)){
            printf("yes\n");
        }
        else{
            printf("no\n");
        }

        close(client_sockfd);
    }


}