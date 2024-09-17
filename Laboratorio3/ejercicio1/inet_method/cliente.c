#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#define BUF_SIZE 100
int main(int argc,char *argv[]){
    struct sockaddr_in address; //sockaddr_in para internet
    char ch = 'A';
    if(argc !=2)exit(1);
    int num = atoi(argv[1]);
    int sfd;
    int result;
    char response[BUF_SIZE];
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

    printf("I write %d\n",num);
    write(sfd,&num,sizeof(int));
    read(sfd,response,BUF_SIZE);
    printf("My number was %d and my response is: %s\n",num,response);
    close(sfd); //cierro la conexioon
    exit(0);
}