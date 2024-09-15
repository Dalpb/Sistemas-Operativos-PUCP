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
    ssize_t numRead;
    char buf[BUF_SIZE];

    sfd = socket(AF_UNIX,SOCK_STREAM,0); //crea un socket en local
    if(sfd == -1)
        perror("socket");
    
    memset(&addr,0,sizeof(struct sockaddr_un)); //inicializa la strucutura

    addr.sun_family=AF_UNIX;
    strncpy(addr.sun_path,SV_SOCK_PATH,sizeof(addr.sun_path) -1);

    //buscamos conectarnos al servidor
    if(connect(sfd,(struct sockaddr *)&addr,sizeof(struct sockaddr_un)) == -1)
        perror("connect");
    
    //el cliente lee desde un stdin el contenido
    while((numRead = read(STDIN_FILENO,buf,BUF_SIZE))>0){
         //el contenido de stdin leido lo manda al socket del servidor por medio de sfd con write
        if(write(sfd,buf,numRead) != numRead)
            perror("partial/failed write");
    }

    if(numRead == -1)
        perror("read");
    
    exit(EXIT_SUCCESS);
}