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

int main(int argc, char *argv[]){

    struct sockaddr_un addr;
    int sfd;
    ssize_t numRead;

    char buf[BUF_SIZE];

    sfd = socket(AF_UNIX,SOCK_STREAM,0);
    if(sfd == -1)perror("socket");

    memset(&addr,0,sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path,SV_SOCK_PATH,sizeof(addr.sun_path)-1);

    //realiza la conexion
    if(connect(sfd,(struct sockaddr *)&addr,sizeof(struct sockaddr_un))==-1){
        perror("connect");
    }

    while((numRead = read(STDIN_FILENO,buf,BUF_SIZE))>0){
        if(write(sfd,buf,numRead) != numRead){
            perror("parital/failed write");
        }
    }
    if(numRead == -1 )perror("read");

    exit(EXIT_SUCCESS);
}