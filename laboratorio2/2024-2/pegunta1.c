#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main(int argc,char *argv[]){

    if(argc != 2){
        exit(1);
    }
    pid_t padre = getpid();
    int n = atoi(argv[1]);
    int pipes[n+1][2];
    int index = 0; 
    //create pipes
    for(int i=0;i<n+1;i++)pipe(pipes[i]);
    //create process
    for(int i=0;i<n;i++){
        if(!fork()){
            index = i+1; //process pipe index
        }
        else break;
    }

    //write pids
    pid_t mypid = getpid();
    for(int i=0;i<n+1;i++)write(pipes[i][1],&mypid,sizeof(pid_t));

    for(int i=0;i<n+1;i++)close(pipes[i][1]);
    wait(NULL);
    pid_t pid;
    while(read(pipes[index][0],&pid,sizeof(pid_t)) != 0){
        printf("%d    %d\n",(int)mypid,(int)pid);
    }
    printf("---------------------\n");

    for(int i=0;i<n+1;i++)close(pipes[i][0]);
    return 0;
}