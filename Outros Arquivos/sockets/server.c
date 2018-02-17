/** Simple server using sockets
**/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#define TAMMSG 80

int main()
{       
    int sock;                                          
    struct sockaddr_in server; 

    struct sockaddr client;
    socklen_t sc = sizeof(struct sockaddr);                               
 
    int j;
      
    int rval, i=0, f, s0;                                          
    char msg[TAMMSG],porta[16] ;
                                                               
    /* Cria socket. */                  

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {                                            
      fprintf(stderr,"Erro ao abrir stream socket");                 
      return(1);                                           
    } 
         
    printf("Porta:"); fflush(stdin);                                                          
    gets(porta);
    printf("Servidor esperando mensagens na porta .%s.\n",porta);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;                         
    server.sin_port = htons(atoi(porta)); 
    if (bind(sock, (struct sockaddr *)&server, sizeof server ) < 0) {
        fprintf(stderr,"Binding stream socket");                 
        return(1);
    }


    /*Aguarda conexoes do cliente */ 
       
    listen(sock,5);
    
    while (1) {
    
      s0 = accept(sock,&client,&sc);
   
      i++;
      printf("Talking to %d.%d.%d.%d \n",client.sa_data[2]&0x000000ff,
                                         client.sa_data[3]&0x000000ff,
                                         client.sa_data[4]&0x000000ff,
                                         client.sa_data[5]&0x000000ff); 

      f = fork();
    
      if (f == 0) {
        do {
           rval = recv(s0, msg, TAMMSG, 0) ;
           msg[rval] = 0;
	   printf("%d:%s\n",i,msg);
	} while (msg[0] != '.'); 
   
        close(s0);
        return(0);
      }  
   
   }
   
   close(sock);
   return(0);
   
 } 
