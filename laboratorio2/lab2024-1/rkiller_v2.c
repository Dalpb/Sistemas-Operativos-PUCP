#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int main(int argc,char *argv[]){
    if(argc != 2){
        printf("You must put an argument");
        exit(0);
    }
    int nprocs = atoi(argv[1]);
    pid_t root = getpid(),child,pid;
    int fd[2],fd2[2];
    pipe(fd);
    pipe(fd2);
    srand(time(NULL));
    for(int i=0; i<nprocs;i++){
        if(!fork()){
            pid = getpid();
            write(fd[1],&pid,sizeof(pid_t));
        }
        else break;
    }
    close(fd[1]);
    if(getpid()== root){
        pid_t pids[nprocs];
        int i=0;
        while(fd[0],&pid,sizeof(pid_t)){
            pids[i] = pid;
            i++;
        }
        close(fd[0]);
        int random = rand()%nprocs;
        pid_t pid_random = pids[random];
        for(int j=0;j<nprocs;j++){
            if(pids[i] == pid_random)pids[i] = getpid();
            write(fd2[1],&pids[i],sizeof(pid_t));
        }
        close(pids[1]);
    }else{
        
    }
    return 0;
}