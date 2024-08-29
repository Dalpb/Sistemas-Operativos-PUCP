#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
int main(int argc,char *argv[]){
    int fd[2];
    pid_t padre = getpid();
    pipe(fd);

    if(!fork()){
        pid_t pid = getpid();
        char str[20];
        sprintf(str,"pstree -spl %d",(int)pid);
        system(str);
        kill(padre,SIGTERM);
        system(str);
        exit(1);
    }
    else{
        close(fd[1]);
        read(fd[0],&padre,sizeof(padre)); //this will block the process, will wait any data in the pipe
        exit(1);
    }
    return 0;
}