#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define SV_SOCK_PATH "/tmp/us_xfr"
#define BUF_SIZE 100
#define BACKLOG 5

int main(int argc,char *argv[]){
    struct sockaddr_un addr;
    int sfd;
    char response[BUF_SIZE];
    if(argc != 2){
        printf("I need a number as argument , *mewing*  bye bye\n");
        exit(1);
    }
    sfd = socket(AF_UNIX,SOCK_STREAM,0);
    if(sfd == -1)perror("socket");
    

    memset(&addr,0,sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path,SV_SOCK_PATH,sizeof(addr.sun_path)-1);

    if(connect(sfd,(struct sockaddr *)&addr,sizeof(struct sockaddr_un)) == -1)
        perror("connect");
    
    int num = atoi(argv[1]);
    printf("I write %d\n",num);
    write(sfd,&num,sizeof(int));
    read(sfd,response,BUF_SIZE);
    printf("My number was %d and my response is: %s\n",num,response);
    close(sfd);
    exit(1);
}