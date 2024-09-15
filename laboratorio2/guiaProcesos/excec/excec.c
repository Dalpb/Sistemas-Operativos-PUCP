#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(void){
    if(!fork()){
        printf("Soy el hijo \n");
        execl("/home/diego/Documentos/Universidad/SOv2/SO/laboratorio2/guiaProcesos/excec/ola","ola",NULL);
        printf("Soy el hijo \n");
    }
    else printf("Soy el padre\n");
    return 0;
}