#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#define DISPLAY1 "PID INDUK** ** pid (%5.5d) ** *******\n"
#define DISPLAY2 "val1(%5.5d) -- val2(%5.5d) -- val3(%5.5d)\n"

int main(void){
    pid_t val1,val2,val3;
    char str[100];
    pid_t father = getpid();
    printf(DISPLAY1,(int)getpid());
    fflush(stdout);
    val1 = fork();
    waitpid(-1,NULL,WUNTRACED);
    val2= fork();
    waitpid(-1,NULL,WUNTRACED);
    val3 = fork();
    waitpid(-1,NULL,WUNTRACED);
    printf(DISPLAY2,(int)val1,(int)val2,(int)val3);
    if(getpid() == father){
        sprintf(str,"pstree -p %d > multifork.txt",father);
        printf("%s",str);
        system(str);
    }
    else{
        kill(getpid(),SIGSTOP);
    }
    return 0;
}