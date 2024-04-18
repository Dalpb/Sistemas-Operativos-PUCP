#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <signal.h>
#include <pthread.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

void *thread_func(void *tsocket){
    //encascada
    long c_sockfd = (long)tsocket;
    char ch;
    //comunicamos con  el cliente
    read(c_sockfd,&ch,1);
    sleep(5);
    ch++;
    //enviamos al cliente
    write(c_sockfd,&ch,1);
    close(c_sockfd);
    pthread_exit(NULL);
}


int main(){
    int server_sockfd, client_sockfd; //archivos de comunicacion
    int server_len, client_len; //tamaño de las direciones

    //direcciones
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    //creamos un socket
    server_sockfd = socket(AF_INET,SOCK_STREAM,0);

    //config direccion del sv
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(9734);

    //obtengo tamaño
    server_len = sizeof(server_address);

    //indico que esta dispo para conexiones
    bind(server_sockfd,(struct sockaddr *)&server_address,server_len);

    //escucho una conexion con maximo 5 conex pendientes
    listen(server_sockfd,5);


    for(;;){
        pthread_t thread_id; //creo un id hilo
        printf("server waiting\n");


    //acepto conecxion
        client_len = sizeof(client_address); 
        client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);

        int ret = pthread_create(&thread_id,NULL,thread_func,(void *)client_sockfd);
        if(ret !=0){
            printf("Error from pthread: %d\n",ret);
            exit(1);
        }
    }

}