#include <pthread.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#define BACKLOG 5

void *thread_func(void *tsocket){
    long c_sockfd = (long)tsocket;
    char ch;

    read(c_sockfd,&ch,1);
    sleep(5);
    write(c_sockfd,&ch,1);
    close(c_sockfd);
    pthread_exit(NULL);
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
        char ch;
        pthread_t pthread_id;
        printf("server waiting\n");
        client_len = sizeof(client_address);
        //accpet conexion
        client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);

        if(client_sockfd == -1)perror("accept");
        int ret = pthread_create(&pthread_id,NULL,thread_func,(void *)client_sockfd);
        if(ret != 0){
            printf("Error from thread\n");
            exit(1);}
    }
}