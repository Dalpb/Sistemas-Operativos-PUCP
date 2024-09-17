#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#define BACKLOG 5
#define PORT 9347
const 
int main(int argc,char *argv[]){
  int server_sockfd, client_sockfd;
    struct sockaddr_in server_address, client_address;
    socklen_t client_len;
    char buffer[1024];

    // Crear un socket IPv4, TCP (stream)
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sockfd == -1) {
        perror("Error creando el socket");
        exit(1);
    }

    // Configuración de la dirección del servidor
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;  // Aceptar conexiones en cualquier interfaz
    server_address.sin_port = htons(PORT);  // Puerto

    // Enlazar el socket a la dirección y puerto
    if (bind(server_sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {
        perror("Error en bind");
        exit(1);
    }

    // Escuchar conexiones entrantes
    if (listen(server_sockfd, BACKLOG) == -1) {
        perror("Error en listen");
        exit(1);
    }

    printf("Servidor web escuchando en el puerto %d...\n", PORT); //indico que el servidor recibe solicituees

    while (1) {
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
        if (client_sockfd == -1) {
            perror("Error en accept");
            continue;
        }

        // Leer la solicitud del cliente GET que realiza el navegador
        read(client_sockfd, buffer, sizeof(buffer) - 1);
        printf("Solicitud recibida:\n%s\n", buffer);  // Imprimir la solicitud en la consola

        // Crear la respuesta HTTP con contenido HTML
        const char *response = 
            "HTTP/1.1 200 OK\r\n" //protocol http , response OK
            "Content-Type: text/html\r\n" //tipo text/html
            "Connection: close\r\n" 
            "\r\n"
            "<!DOCTYPE html>" //contenido de body de response
            "<html>"
            "<head><title>Servidor Web en C</title>"
            "<style>"
            "body{background-color:#333;color:#fff;min-height:100vh;display:flex;align-items:center;justify-content:center;flex-direction:column}"
            "</style>"
            "</head>"
            "<body><h1>Hola, Mundo desde C!</h1><button id=\"btn\">Click <span id=\"number\">0</span></button>"
            "<script>const btn=document.getElementById(\"btn\");const span=document.getElementById(\"number\");btn.addEventListener(\"click\",()=>{span.innerText = parseInt(span.innerText) + 1;;})</script>"
            "</body>"
            "</html>";

        // Enviar la respuesta al cliente
        write(client_sockfd, response, strlen(response));

        // Cerrar la conexión con el cliente
        close(client_sockfd);
    }

    // Cerrar el socket del servidor
    close(server_sockfd);

    return 0;

}