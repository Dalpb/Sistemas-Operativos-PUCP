#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

int main(int argc,char *argv[]){

    pid_t pid;
    int fd[2];
    pipe(fd);
    if((pid= fork())){
        system("ps -l");
        kill(pid,SIGTERM);
        system("ps -l");
        exit(1);
    }else{
        //block the son
        read(fd[0],&pid,sizeof(pid));
        exit(1);
    }
    
    return 0;
}