#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
int main(int argc,char *argv[]){
    if(argc != 2){
        printf("You must put an argument");
        exit(0);
    }
    int nprocs = atoi(argv[1]);
    int fd[2],i,fd_random[2];

    pid_t pids[nprocs], root = getpid(),child;
    pipe(fd);
    pipe(fd_random);
    srand(time(NULL));

    for(i=0; i<nprocs;i++){
        if((child = fork())==0){
            int pid = (int)getpid();
            printf("%d\n",getpid());
            write(fd[1],&pid,sizeof(pid));
        }
        else break;
    }
    close(fd[1]); //its necessary close every pipe in each process
    if(getpid() == root){
        int pid,j = 0;
        //get all pids created
        while(read(fd[0],&pid,sizeof(pid)) !=0){
            pids[j] = pid;
            j++;
        }
        //get random process
        int random = rand()% (nprocs);
        int pid_random = pids[random];
        printf("Root %d: continue process %d\n",getpid(),pid_random);
        //create another pipe for the random process
        for(int i= 0;i<nprocs;i++){
            //if(pids[i] == pid_random)pids[i] = getpid();
            if(pids[i] == pid_random)continue;

            int pid = pids[i];
            write(fd_random[1],&pid,sizeof(pid));
        }
        pid = getpid();
        write(fd_random[1],&pid,sizeof(pid));
        close(fd_random[1]);
        kill(pid_random,SIGCONT);
    }else{
        close(fd_random[1]);
    }

    kill(getpid(),SIGSTOP); // stop all process

    printf("I'am the process %d\n",getpid());
    char str[100];
    int pid;
    while(read(fd_random[0],&pid,sizeof(pid)) !=0){
        sprintf(str,"pstree -ps %d ",getpid());
        printf("%s - %d\n",str,pid);
        //use sleep for fix syncronized problems between kill and system --> news: if we kill the root process, this doesnt work
        system(str);
        kill(pid,SIGKILL);
    }
    close(fd[0]);
    close(fd_random[0]);
    return 0;
}
