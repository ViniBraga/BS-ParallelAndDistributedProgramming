/** Simple client using sockets
**/


#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

#define TAMMSG 80

int main(int argc, char *argv[])
{

  int s1;

  struct sockaddr_in server;
  struct hostent *hp, *gethostbyname();

  char msg[TAMMSG] ;

  if (argc < 3) {
     printf(" Numero de parametros insuficientes\n") ;
     printf(" Digite o nome do programa, servidor e o numero da porta\n") ;
     return(1) ;
    }
    
  s1 = socket(AF_INET, SOCK_STREAM, 0);

  if (s1  <0) {
     fprintf(stderr,"Error opening stream socket.");
     return(1);
  }

  hp = gethostbyname(argv[1]);
  if (hp == 0) {
     fprintf(stderr,"%s: unkown host",argv[1]);
     return(2);
  }
  
  strncpy((char *)&server.sin_addr,(char *)hp->h_addr, hp->h_length);
  server.sin_family = AF_INET;
  server.sin_port = htons(atoi(argv[2]));
  
  if (connect(s1, (struct sockaddr *)&server, sizeof server ) < 0) {
    fprintf(stderr,"Erro connectando stream socket");
    exit(1);
  }

  printf("Talk\n") ;
  
  do {
         gets(msg);
         printf("Enviei: %s \n",msg);
	 send(s1, msg, strlen(msg), 0);

  } while (msg[0] != '.'); 
  
  close(s1);
  exit(0);
 
}

