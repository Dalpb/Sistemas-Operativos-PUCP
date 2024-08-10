#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
    int i,status;
    pid_t child,pid_padre;
    char str[100];
    pid_padre = getpid();
    //el main crea 3 hijos, hay en total 4procesos
    for(i=1;i<4;i++){
        if((child=fork()) <= 0)break;
        else fprintf(stderr,"Este es el ciclo Nro %d y se esta creando el poceso %d\n",i,child);
    }
    fprintf(stderr,"Este es el proceso %d con padre %d\n",getpid(),getppid());
    if(pid_padre == getpid()){
        sprintf(str,"pstree -p %d > fanp.txt",pid_padre);
        system(str);
    }
    else{
        while(1); //atrapados en bucle
    }
    return 0;
}