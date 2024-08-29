#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main(void){
    int ii=0;
    char str[100];
    pid_t father = getpid();

    if(fork() == 0)ii++; //entra solo los hijos
    waitpid(-1,NULL,WUNTRACED);
    if(fork() == 0)ii++;
    waitpid(-1,NULL,WUNTRACED);
    if(fork() == 0)ii++;
    waitpid(-1,NULL,WUNTRACED);
    printf("Result = %3.3d-- pid : %d\n",ii,getpid());
    fflush(stdout);
  if(getpid() == father){
        sprintf(str,"pstree -p %d > isengfork.txt",father);
        printf("%s",str);
        system(str);
    }
    else{
        kill(getpid(),SIGSTOP);
    }
    return 0;
}