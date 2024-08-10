#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
    pid_t child;
    if((child = fork())){
        fprintf(stderr,"\nFork() devolvio %d por tanto el padre con ID = %d\n",child,getpid());
        wait(NULL);
    }
    else{
        char str[100];
        sprintf(str,"pstree -ps %d > procesos.txt",getppid());
        printf("%s",str);
        system(str); 
        fprintf(stderr,"\nFork() devolvio %d, soy hijo con ID = %d con un padre de ID = %d\n" ,child,getpid(),getppid());

        //el proceso sh se refiere al call system  bash
    }

    return 0;
}