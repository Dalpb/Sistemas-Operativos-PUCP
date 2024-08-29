#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
pid_t padre;
int fd[2];
void creaArbol(int ,int );
int main(int argc,char *argv[]){

    if(argc != 2){
        printf("You must enter a n dep\n");
        exit(1);
    }
    int n = atoi(argv[1]);
    if(n < 1) {
        printf("The argument must be greater than 1\n");
        exit(1);
    }
    padre = getpid();
    pipe(fd);
    creaArbol(n,0);
    return 0;
}
void creaArbol(int n,int i){
    int pid;
    if(i == n){
        //stop tree
        pid = getpid();
        printf("%d",pid);
        write(fd[1],&pid,sizeof(pid)); //comunication  
        for(;;);
    }

    for(int j=0;j<n;j++){
        if(!fork())creaArbol(n,i+1);
    }

    if(getpid() == padre){
        read(fd[0],&pid,sizeof(pid)); 
        char str[50];
        sprintf(str,"pstree -p %d",getpid());
        system(str);
    }
    for(int j=0; j<n;j++){
        wait(NULL);
    }
}