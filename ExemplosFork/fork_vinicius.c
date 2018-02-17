#include <stdio.h>
#include <xlocale.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <stdbool.h>

#define TAMMSG 80

bool ehprimo(int num);

int main(int argc, char **argv){

    int fd[2], nbytes, i=0;
    pid_t pid1, pid2;
    char string[TAMMSG];
    char msgParaPai[TAMMSG];
    int valorRecebidoPeloFilho;
    char msgFinalRecebidaPeloPai[TAMMSG];

    time_t begin_t, end_t;

    pipe(fd);

    if(argc <= 1){
      printf("*Informar mais valores!\n\n");
      return 0;
    }

    if((pid1 = fork()) == -1){
        printf("*Erro ao criar processo = %d.\n",pid1);
        return(1);
    }
    if(pid1 == 0){
        nbytes = read(fd[0], &valorRecebidoPeloFilho, 8);
        printf("*Filho recebeu %d do pai\n", valorRecebidoPeloFilho);

        bool ehPrimo = ehprimo(valorRecebidoPeloFilho);
        if(ehPrimo){
          sprintf(msgParaPai,"%d é primo",valorRecebidoPeloFilho);
        }
        else{
          sprintf(msgParaPai,"%d não é primo",valorRecebidoPeloFilho);
        }

        printf("*Filho verifica que %s",msgParaPai);
        write(fd[1], msgParaPai, (sizeof(string)+1));

    }
    else{
        int valor = atoi(argv[1]);
        printf("\n*Pai recebeu %d e o enviará ao filho...\n\n", valor);
        write(fd[1], &valor, (sizeof(int)));
        sleep(2);
        nbytes = read(fd[0], msgFinalRecebidaPeloPai, 15);
        printf("\n\n*Pai recebeu do filho mensagem dizendo que %s\n", msgFinalRecebidaPeloPai);


        printf("\n");
    }
    return(0);

}

bool ehprimo(int num){
  int f = 1, i;
  for(i = 2; i <= num/2; i++){
    if(num % i == 0){
      f = 0;
      break;
    }
  }
  return f;
}
