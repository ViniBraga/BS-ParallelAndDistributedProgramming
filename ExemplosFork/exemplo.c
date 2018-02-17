#include <stdio.h>
#include <unistd.h> //para o pid_t

int main()
{
    pid_t pid;

    printf("Oi!\n");

    pid = fork(); //Código é replicado a partir daqui
    printf("Erroooooouuuu!\n");

    if(pid == -1)
    {
      printf("Erro ao criar processo %d\n", pid);
    }

    if(pid == 0)
    {
      printf("Eu sou o processo filho. Meu ID é %d\n", pid);
    }
    else
    {
      printf("Eu sou o processo pai. Meu ID é %d\n", pid);
    }

    return 0;
}
