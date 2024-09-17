/**********************************************************************\
*                Copyright (C) Michael Kerrisk, 2010.                  *
*                                                                      *
* This program is free software. You may use, modify, and redistribute *
* it under the terms of the GNU Affero General Public License as       *
* published by the Free Software Foundation, either version 3 or (at   *
* your option) any later version. This program is distributed without  *
* any warranty. See the file COPYING for details.                      *
\**********************************************************************/

/* us_xfr_cl.c

   An example UNIX domain stream socket client. This client transmits contents
   of stdin to a server socket.

   See also us_xfr_sv.c.
*/

#include <sys/un.h>
#include <sys/socket.h>
#include <sys/types.h>  /* Type definitions used by many programs */
#include <stdio.h>      /* Standard I/O functions */
#include <stdlib.h>     /* Prototypes of commonly used library functions,
                           plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>     /* Prototypes for many system calls */
#include <errno.h>      /* Declares errno and defines error constants */
#include <string.h>     /* Commonly used string-handling functions */


#define SV_SOCK_PATH "/tmp/us_xfr"

#define BUF_SIZE 200
#define RESPONSE_SIZE 600


int
main(int argc, char *argv[])
{
    struct sockaddr_un addr;
    int sfd;
    ssize_t numRead;
    char buf[BUF_SIZE];
    char response[RESPONSE_SIZE];
    sfd = socket(AF_UNIX, SOCK_STREAM, 0);      /* Create client socket */
    if (sfd == -1)
        perror("socket");

    /* Construct server address, and make the connection */

    memset(&addr, 0, sizeof(struct sockaddr_un));
    addr.sun_family = AF_UNIX;
    strncpy(addr.sun_path, SV_SOCK_PATH, sizeof(addr.sun_path) - 1);

    if (connect(sfd, (struct sockaddr *) &addr,
                sizeof(struct sockaddr_un)) == -1)
        perror("connect");

    /* Copy stdin to socket */
    //read cmd 
    numRead = read(STDIN_FILENO,buf,BUF_SIZE);
    if(numRead == -1)
        perror("read");
    //send request in socket
    if(write(sfd,buf,numRead) == -1)
        perror("partial/failed write");

    if(read(sfd,response,RESPONSE_SIZE) == -1)
        perror("read response");
    
    printf("%s",response);
    exit(EXIT_SUCCESS);         /* Closes our socket; server sees EOF */
}
