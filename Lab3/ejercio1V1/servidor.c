#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <errno.h>
#include <string.h>

#define SV_SOCK_PATH "/tmp/us_xfr"
/* Version localhost */

int esPrimo(int num){
    int div =0 ;
    for(int i=1; i<=num;i++){
        if(num%i == 0)div++;
    }
    return div==2 ? 1: 0;
}
int main(int argc, char *argv[]){

    int sfd,cfd;
    struct sockaddr_un address;
    sfd = socket(AF_UNIX,SOCK_STREAM,0);
    if(sfd == -1)perror("No creo el socket");

    if(remove(SV_SOCK_PATH) == -1 && errno != ENOENT)perror("remove");


    //si o si debe estar
    memset(&address,0,sizeof(struct sockaddr_un));
    address.sun_family = AF_UNIX;
    strncpy(address.sun_path,SV_SOCK_PATH,sizeof(address.sun_path)-1);

    //disponible para una conexion
    if(bind(sfd,(struct sockaddr *)&address,sizeof(struct sockaddr_un) ) == -1)perror("bind");

    //dispuestos a escuchar
    if(listen(sfd,5) == -1)perror("listed");

    for(;;){
        int num;
        cfd = accept(sfd,NULL,NULL);
        if(cfd == -1)perror("accept");

        read(cfd,&num,sizeof(num));
        if(esPrimo(num)){
            printf("yes\n");
        }else{
            printf("no\n");
        }

        close(cfd);
        
    }   
}