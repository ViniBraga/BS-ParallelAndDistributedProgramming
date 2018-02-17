/** Programa que cria processo pesado usando fork. Usa pipe para comunicação entre os
processos. Processo filho faz algo (no exemplo ele só dorme) e envia o tempo que levou
para fazer este algo para o pai. Além disso, cada um incrementa uma variável i.
*/

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>

#define TAMMSG 80

int main()
{
  int fd[2];
  int nbytes;
  int i = 0;

  pid_t pid;

  char string[TAMMSG];
  char buffer[TAMMSG];

  time_t begin_t;
  time_t end_t;

  pipe(fd);

  if((pid = fork()) == -1)
  {
    printf("Erro ao criar processo %d.\n", pid);
  }

  if(pid == 0) // Código para o processo filho
  {
    begin_t = time(NULL);
    printf("Filho iniciou...\n");
    sleep(3); //Faz algo. No caso, dorme.
    end_t = time(NULL);

    sprintf(string, "%3.0f", difftime(end_t, begin_t));
    write(fd[1], string, (strlen(string)+1));

    i++;
    printf("Filho terminou: valor de i é %d\n", i);

  }
  else // Código para o processo pai. Lê algo que foi enviado pelo filho.
  {
    nbytes = read(fd[0], buffer, 8);

    printf("Pai: recebeu %s (%d)\n", buffer, nbytes);
    i++;
    printf("Pai: valor de i é %d\n", i);

  }

  return 0;
}
