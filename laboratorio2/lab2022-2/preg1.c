#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc,char * argv[]){
    int nf,j;
    nf = atoi(argv[1]);
    pid_t padre = getpid();
    for(j=0;j<nf;j++){
        fork();
    }
    if(padre == getpid()){
        char str[20];
        sprintf(str,"pstree -p %d",getpid());
        system(str);
        killall();
        system(str);
    }else{
        pause();
    }

    return 0;
}