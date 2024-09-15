#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
pid_t padre;
int hojas;
int fd[2];
void creaArbol(int ,int );
int main(int argc,char *argv[]){
    if(argc != 2)exit(1);
    int n = atoi(argv[1]);
    hojas = pow(n,n);
    padre = getpid();
    pipe(fd);

    creaArbol(0,n);
    return 0;
}
void creaArbol(int i,int n){
    pid_t pid =getpid();
    printf("%d",i);
    if(i == n){
        write(fd[1],&pid,sizeof(pid_t));
        for(;;);
    }else{
        for(int j=0;j<n;j++){
            if(!fork()){
                creaArbol(i+1,n);
                break;
            }
        }
        if(getpid() == padre){
            for(int i=0;i<hojas;i++){
                read(fd[0],&pid,sizeof(pid_t));
            }
            char str[20];
            sprintf(str,"pstree -p %d",(int)getpid());
            system(str);
            for(;;);
        }
        for(int i=0;i<n;i++)wait(NULL);        
    }
}