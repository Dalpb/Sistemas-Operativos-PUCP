#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 3
int main(void){
    int i;
    int root = getpid();
    char str[30];
    for(i=1;i<N;i++){
        fork();
        fork();
    }
    printf("PID[%3.3d]\n",getpid());
    fflush(stdout);
    if(root == getpid()){
        sleep(1); //sleep for creation of all process
        sprintf(str,"pstree -p %d",root);
        system(str); 
        wait(NULL); //wait  ,stop that root process dead
    }
    else{
        while(1);
    }
    exit(0);

}