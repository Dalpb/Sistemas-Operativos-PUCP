#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

int main(int argc,char*argv[]){
    if(argc != 2){
        printf("Use: ./swapTwo n");
        exit(1);
    }
    int n = atoi(argv[1]);
    int fdPar[2] , fdImpar[2];
    pipe(fdPar);
    pipe(fdImpar);
    pid_t padre = getpid();
    
    for(int i=0;i<2;i++){
        if(!fork()){
            //hijo entra
            pid_t miPid = getpid();
            srand(miPid);
            int num;
            for(int j=0;j<n;j++){
                num = rand() % 520;
                printf("Antes: My pid=%d my number=%d\n",(int)miPid,num);
                if(num % 2 == 0)write(fdPar[1],&num,sizeof(num));
                else write(fdImpar[1],&num,sizeof(num));
            }
            close(fdImpar[1]);
            close(fdPar[1]);

            if(((int)miPid) % 2 == 0){
                while(read(fdPar[0],&num,sizeof(num))!= 0){
                    printf("Después: My pid=%d my number=%d\n",(int)miPid,num);
                }
            }
            else{
                while(read(fdImpar[0],&num,sizeof(num))!= 0){
                    printf("Después: My pid=%d my number=%d\n",(int)miPid,num);
                }              
            }
            close(fdImpar[0]);
            close(fdPar[0]);
            break;
        }
    }

    if(getpid() == padre){
        close(fdImpar[1]);
        close(fdImpar[0]);
        close(fdPar[1]);
        close(fdPar[0]);
        for(int i=0; i<2;i++){
            wait(NULL);
        }
    }
    return 0;
}