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
    int sfd,cfd;
    ssize_t numRead;
    char buf[BUF_SIZE];
    //retorna descriptor de archivo
    sfd = socket(AF_UNIX,SOCK_STREAM,0);
    if(sfd == -1)perror("socket creation");
//limina cualquier archivo existente con el mismo pathname que el que queremos ligar al socket.
    if(remove(SV_SOCK_PATH)== -1 && errno != ENOENT)
        perror("remove");

    memset(&addr,0,sizeof(struct sockaddr_un));   
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path,SV_SOCK_PATH, sizeof(addr.sun_path)-1);

//busca alguna conexion
    if(bind(sfd,(struct sockaddr *)&addr,sizeof(struct sockaddr_un)) ==-1)
        perror("bind");

    if(listen(sfd,BACKLOG) == -1)
        perror("listen");

    for(;;){
        cfd = accept(sfd,NULL,NULL);
        if(cfd == -1)
            perror("accept");

        while((numRead = read(cfd,buf,BUF_SIZE)) >0)
            if(write(STDOUT_FILENO,buf,numRead) != numRead)
                perror("partial/failed write");

        if(numRead == -1)perror("read");
        if(close(cfd) == -1)perror("close");
    }   
}