#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
    int i,status;
    pid_t child;
    char str[100];
     // -p muestra los hijos del proceso
    pid_t pather = getpid();
    //genera 4 procesos
    for(i=1;i<4;i++){
        if((child = fork())){
            break;
        }    
    }

    fprintf(stderr,"Esta es la vuelta Nro %d\n",i);
    fprintf(stderr,"Recibi de fork el valor %d\n",child);
    fprintf(stderr,"Soy el proceso %d con padre %d\n\n",getpid(),getppid());

    if(child != 0)wait(&status);
    else{
        sprintf(str,"pstree -p %d > chainp.txt",pather);
        printf("%s",str);
        system(str);
    }

    return 0;   
}