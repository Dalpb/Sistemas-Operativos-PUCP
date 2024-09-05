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
    pid_t padre = getpid(), child;
    pid_t pid;
    char str[20];
    pipe(fd);
    for(int i=0 ; i< n ;i++){
        if((child = fork())){
            //pathers not continue loop
            break;
        }
    }
    if(getpid() == padre){
        close(fd[1]);
        sprintf(str,"pstree -p %d",padre);
        while(read(fd[0],&pid,sizeof(pid_t)) > 0 ){
            system(str);
            kill(pid,SIGTERM);
            printf("%d\n",(int)pid);
        }
        kill(pid,SIGKILL); //should kill the last process 
        wait(NULL);
        system(str);
        printf("Se termino\n");
        fflush(stdout);
        close(fd[0]);
    }
    else{
        close(fd[0]);                                                              ;
        wait(NULL); //everybody will wait
        pid=getpid();
        write(fd[1],&pid,sizeof(pid_t));
        if(close(fd[1]) == -1){
            printf("No cerro con exito - %d\n",getpid());
        }
        for(;;);
    }
    return 0;
}