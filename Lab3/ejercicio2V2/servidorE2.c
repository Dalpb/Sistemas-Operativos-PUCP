#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

void Fibonnachi(int lim){
    int fn_1 = 1,fn_2  = 0, fn;

    for(int i=0;i<lim;i++){
        if(i<=1){
            fn = i;
        }
        else{
            fn = fn_1+fn_2;
            fn_2 = fn_1;
            fn_1 = fn;
        }
        printf("%d  ", fn);
    }
    printf("\n");
}
int main(){
    int server_sfd, client_sfd;
   int server_len,client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    server_sfd = socket(AF_INET,SOCK_STREAM,0);

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port =  htons(9734);
    server_len = sizeof(server_address);

    bind(server_sfd,(struct sockaddr *)&server_address,server_len);

    listen(server_sfd,5);

    for(;;){
        printf("Server waiting\n");
        client_len = sizeof(client_address);
        client_sfd=accept(server_sfd,(struct sockaddr *)&client_address,&client_len);
        
        int num;
        read(client_sfd,&num,sizeof(num));
        Fibonnachi(num);
        close(client_sfd);
    }
}