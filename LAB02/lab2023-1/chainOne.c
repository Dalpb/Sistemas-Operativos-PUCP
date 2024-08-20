#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define OK 1

int main(int argc,char *argv[]){
    if(argc != 2){
        printf("Use ./chainOne #process\n");
        exit(OK);
    }
    int n = atoi(argv[1]),fd[2];
    pid_t padre = getpid(), pid;
    char str[20];
    pipe(fd);
    for(int i=0 ; i< n ;i++){
        if(!fork()){
            pid= getpid();
            close(fd[0]);           
            write(fd[1],&pid,sizeof(pid));
        }
        else break;
    }
    if(getpid() != padre){
        close(fd[1]);
        for(;;);
    } //will block
    else{
        close(fd[1]);
        sprintf(str,"pstree -p %d",getpid());
        pid_t pidArr[n];
        int i=n-1;
        while(read(fd[0],&pid,sizeof(pid))!=0){
            pidArr[i] = pid;
            i--;
        }

        close(fd[0]);
        for(int j=0 ;j<n;j++){
            kill(pidArr[j],SIGTERM);
            printf("%d  ",pidArr[j]);
            fflush(stdout);
            system(str);
        }
    }
    return 0;
}