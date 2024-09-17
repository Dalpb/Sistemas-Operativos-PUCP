#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#define BACKLOG 5
#define SV_SOCK_PATH "/tmp/us_xfr"
int fibonachi(int n,int socket_client){
    int temp1 = 0, temp2 = 1,num;
    num=0;
    if(n > 0)write(socket_client,&num,sizeof(int));
    num = 1;
    if(n > 1)write(socket_client,&num,sizeof(int));

    for (int i = 2; i < n; i++){
        num = temp1 + temp2;
        write(socket_client,&num,sizeof(int));
        temp1 = temp2;
        temp2 = num;
    }
}
int main(){
    struct sockaddr_un addr;
    int sfd,cfd;

    sfd = socket(AF_UNIX,SOCK_STREAM,0);
    if(sfd == -1)perror("socket creation");
    if(remove(SV_SOCK_PATH)== -1 && errno != ENOENT)
        perror("remove");

    memset(&addr,0,sizeof(struct sockaddr_un));   
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path,SV_SOCK_PATH, sizeof(addr.sun_path)-1);

    if(bind(sfd,(struct sockaddr *)&addr,sizeof(struct sockaddr_un)) ==-1)
        perror("bind");
//cuando encuentra la xonexión para aceptarla
    if(listen(sfd,BACKLOG) == -1)
        perror("listen");

    while (1){
        int num;
        char response[5];
        cfd = accept(sfd,NULL,NULL);
        if(cfd == -1)perror("accept");

        if(!fork()){
            read(cfd,&num,sizeof(int));
            fibonachi(num,cfd);
            close(cfd);
            exit(0);
        }else{
            close(cfd);
        }
    }
    
    
}