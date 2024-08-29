#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void usage(char *);
int main(int argc,char *argv[]){
    char comando[30];
    int fd[2];

    pipe(fd);

    if(argc != 2)usage(argv[0]);
    sprintf(comando,"ls -l %s | grep ^-",argv[1]);
    system(comando);
    return 0;
}
void usage(char *prog){
    fprintf(stderr,"Uso: %s <ruta_del_directorio>\n",prog);
    exit(1);
}

