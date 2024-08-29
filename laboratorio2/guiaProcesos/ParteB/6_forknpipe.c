#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define BUFSIZE 64
int main(void){
    char buffer[BUFSIZE];
    char message[] = "This is a message";
    int pipes[2], i; // pipe[0] escribe
    //creamos comunicacion
    if(pipe(pipes) == -1){
        printf("Can not be able to create a pipe");
        exit(0);
    };

    if(!fork()){ //para el hijo
        close(pipes[1]); //solo leera
        printf("I am PID[%d] (child) \n",(int)getpid());
        fflush(stdout);
        memset(buffer,0,sizeof(buffer)) ; //inicaliza el array con 0
        //bufsize-1 para que exista espacio para el caracter nulo
        while(read(pipes[0],buffer,BUFSIZE -1) != 0){ //hasta que llegue a EOF
            printf("I recived this: %s \n",buffer);
            memset(buffer,0,sizeof(buffer)); //reinicio el buffer
        }
        close(pipes[0]);
    }
    else{
        close(pipes[0]); //solo el padre escribe
        printf("I am PID [%d] parent \n",getpid());
        fflush(stdout);
        for(i=0;i<10;i++){
            write(pipes[1],message,sizeof(message)-1);
        }
        close(pipes[1]);
    }
    return 0;
}