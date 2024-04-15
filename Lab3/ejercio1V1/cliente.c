#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>

#define SV_SOCK_PATH "/tmp/us_xfr"

int main(int argc, char *argv[]){
    struct sockaddr_un addr;
    int sfd;   

    if(argc <2){
        printf("No se ingreso un numero");
        exit(0);
    }
    sfd = socket(AF_UNIX,SOCK_STREAM,0);

    memset(&addr,0,sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path,SV_SOCK_PATH,sizeof(addr.sun_path)-1);

    //realiza la conexcion
    if(connect(sfd,(struct sockaddr *)&addr,sizeof(struct sockaddr_un))==-1){
        perror("connect");
    }


    int num= atoi(argv[1]);
    write(sfd,&num,sizeof(num));
    close(sfd);
    exit(0);
}