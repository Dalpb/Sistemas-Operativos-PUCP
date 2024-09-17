#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    struct sockaddr_in address; //sockaddr_in para internet
    char ch = 'A';
    int sfd;
    int result;
    int len;
    sfd = socket(AF_INET,SOCK_STREAM,0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port=htons(9734);
    len= sizeof(address);

    result = connect(sfd,(struct sockaddr *)&address,len);
    
    if(result == -1){
        perror("oops: client");
        exit(1);
    }

    write(sfd,&ch,1); //le mando un requeest al servidor
    read(sfd,&ch,1); //leo lo obtenido
    printf("char from server = %c\n",ch);
    close(sfd); //cierro la conexioon
    exit(0);
}