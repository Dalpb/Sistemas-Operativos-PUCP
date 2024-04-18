#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>



int main(int argc, char *argv[]){
    struct sockaddr_in address;
    int sfd;   
    int address_len;
    if(argc <2){
        printf("No se ingreso un numero");
        exit(0);
    }
    sfd = socket(AF_INET,SOCK_STREAM,0);

    //representa el hosting
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(9734);
    address_len = sizeof(address);


    //realiza la conexcion
    if(connect(sfd,(struct sockaddr *)&address,address_len)==-1){
        perror("connectsdadsad");
    }

    int num= atoi(argv[1]);
    write(sfd,&num,sizeof(num));
    close(sfd);
    exit(0);
}