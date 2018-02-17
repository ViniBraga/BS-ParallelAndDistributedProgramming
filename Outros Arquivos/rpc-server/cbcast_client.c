
/** Client to start a thread in a RPC server.

    Client will call the start routine and send and IP address as parameter (char *).

    In order to work, there must be two servers installed in different machines, 
    for example, 10.32.191.100 and 10.32.191.123. 

    Client will run and connect to one of the servers, for example, 10.32.191.100. 
    After server 10.32.191.100 is started by the client, it will connect to 
    the other server, for example, 10.32.191.123 and call a simple routine called
    NUMBER, and this routine will return value 15 to the server. The server that was
    activated by the client will create a file called cbcast.log.<processid>.

   Run:
     rpcgen cbcast.x
     gcc cbcast_client.c cbcast_clnt.c -o cli
     gcc cbcast_server.c cbcast_svc.c cbcast_clnt.c -pthread -o ser

   Order to run:

    run servers
    run client - client server1 server2
**/


#include <stdio.h>
#include <stdlib.h>
#include <rpc/rpc.h>
#include "cbcast.h"

main(int argc, char *argv[]) {

    CLIENT *cl;
    int *answer;
    char *message;
    void *pvoid;

    if (argc != 3) {
        printf("Usage: %s server myip\n", argv[0]); 
        return (1); 
    } 

    if (!(cl = clnt_create(argv[1], CBCASTPROG,CBCASTVERS,"tcp"))) { 
        clnt_pcreateerror(argv[1]); 
        return(1); 
    } 

   /** Start - send an IP address to the server**/

    message = argv[2];

    answer = start_1(&message,cl); 

    if (answer == (int *) NULL) { 
        printf("Error: state could not produce meaningful results"); 
        return(1); 
    } 

    printf("State = %d\n", *answer); 


    return (0);
} 
