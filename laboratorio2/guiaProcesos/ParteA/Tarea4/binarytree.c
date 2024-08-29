#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double final;
pid_t padre;
int crear_arbol(int);
int main(int arg,char *argv[]){
    int n;
    n=atoi(argv[1]);
    padre = getpid();
    final = pow(2,(n-1));
    crear_arbol(1);
    return 0;
}
int crear_arbol(int x){
    char cadena[60];

    sprintf(cadena,"Soy proceso %d con pid %d y ppid %d\n",x,getpid(),getppid());
    write(1,cadena,strlen(cadena));
    if(x >= final){
       return kill(getpid(),SIGSTOP); //todos los de mayor profundidad se detienen 
    }
    if(!fork()){
        crear_arbol(2*x);
        exit(0);
    }
    if(!fork()){
        crear_arbol(2*x+1);
        exit(0);
    }
    waitpid(-1,NULL,WUNTRACED); //los que son padres se quedan esperando a que sus hijos se detengan
    waitpid(-1,NULL,WUNTRACED); 

    if(getpid() == padre){ // si es padre
        char str[100];
        sprintf(str,"pstree -p %d > binarytree.txt",padre);
        system(str);
        return 1;
    }else{
        return kill(getpid(),SIGSTOP); //los hijos creados se detienen
    }

}
