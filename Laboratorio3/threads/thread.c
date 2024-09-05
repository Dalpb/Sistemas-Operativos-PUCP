#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define N_THREADS 10

void *print_hello_world(void *tid){
   long id = (long)tid;
   fprintf(stderr,"Hello World, Greetings from thread %ld\n",id);
   pthread_exit(NULL);
}

int main(int argc,char *argv[]){
    pthread_t threads[N_THREADS];
    int status;
    long i;

    for(i=0;i<N_THREADS;i++){
        printf("Main here, Creating thread %d\n",i);
        status = pthread_create(&threads[i],NULL,print_hello_world,(void *)i);
        if(status != 0){
            printf("pthread create returned error code %d\n",status);
            exit(1);
        }
        exit(0);
    }
}