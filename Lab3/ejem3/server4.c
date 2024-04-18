#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <signal.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

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

    signal(SIGCHLD, SIG_IGN); //chatgpt, evita procesos zombies

    for(;;){
        char ch;

        printf("server waiting\n");

        //acepta conexion
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address,&client_len);

        //creamos un hijo
        if(fork() == 0){
            //ingresa el hijo, pero mantiene conexion con el cliente,hereda el socket abierto
            read(client_sockfd,&ch,1);
            sleep(5);
            ch++;
            write(client_sockfd,&ch,1);
            close(client_sockfd) ; //cierra comunicacion
            exit(0); //muere el hijo
        }
        else{
            //el padre termina su conexion con cliente y acepta otras conexiones,
            //mientras el hijo se comunica con el cliente
            close(client_sockfd);
        }

    }

}