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
    int fd_pipe[4][2],ii,jj;
    char buffer1[BUFSIZE],buffer2[BUFSIZE]; 
    int p_this,p_prev,p_no1,p_no2;
    pid_t mypid;

    //incializamos
    memset(buffer1,0,BUFSIZE);
    memset(buffer2,0,BUFSIZE);

    for(ii=0;ii<4;ii++)pipe(fd_pipe[ii]);

    ii = fork()!= 0 ? 0: 2; 
    jj = fork()!= 0 ? 0: 1;
    // cada procseso cierra respectivas pipes
    p_this= ii+jj; //el padre-> 0,hijo1-> 2,hijo2 ->1 , hijo3-> 3
    close(fd_pipe[p_this][0]); //cada proceso con su respectivo pipe[num] no podra leer 

    p_prev = (p_this + 3)%4;//refiere al proceso anterior del proceso respectivo
    close(fd_pipe[p_prev][1]); //solo se podra leer

    //las tuberias que no son adyacentes se cierran
    p_no1 = (p_this + 1)%4;
    close(fd_pipe[p_no1][0]);
    close(fd_pipe[p_no1][1]);

    p_no2 = (p_this+2)%4;
    close(fd_pipe[p_no2][0]);
    close(fd_pipe[p_no2][1]);

    mypid= getpid();

    //el proceso escribe un mensaje en su respectivo pipe
    sprintf(buffer1,"  A messae from PID[%d]\n",(int)mypid);
    write(fd_pipe[p_this][1],buffer1,BUFSIZE-1);
    close(fd_pipe[p_this][1]);

    //el proceso lee el mensaje enviado desde un proceso
    while(read(fd_pipe[p_prev][0],buffer2,BUFSIZE-1) !=0){
        waitpid(-1,NULL,0); // asegura que mensejae se envio
        printf("PID[%d] IS WAITING : \n%s\n",mypid,buffer2);
    }
    close(fd_pipe[p_prev][0]);


    return 0;
}