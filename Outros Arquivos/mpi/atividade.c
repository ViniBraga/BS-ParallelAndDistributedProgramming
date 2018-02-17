/**
Atividade com MPI

Criar e executar um programa no qual o processo com rank 0 envia números de 1 até 100 para os outros processos
utilizando a rotina MPI_Send. Os outros processos recebem os números utilizando a rotina MPI_Recv.
Cada processo deve contar o número de valores recebidos que são divisíveis pelo seu rank.
Quando o processo de rank 0 terminar de enviar os números, envia o valor -1 para os outros processos, que, por sua vez,
devem parar de receber números. No final, cada processo imprime seu rank e a quantidade de valores recebidos que
são divisíveis por ele. (Nos slides de aula tem exemplo de envio e recebimento de valores com MPI_Send e MPI_Recv).

Ovservação:
  -Comendo para compilar:
  $ mpicc <nome>.c -o <nome>

  -Comando para executar:
  $ mpirun -np <numero_processos> <nome>

*/
#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int size;
  int rank;
  int valor[0];

  MPI_Init(&argc, &argv); //Inicializa com numero de processos (que é argc)
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); //Seta variável rank como rank do processo (id de cada processo)
  MPI_Comm_size(MPI_COMM_WORLD, &size); //Seta variável size como size do programa (número de processos)

  if(rank == 0)
  {
    int quantidadeValoresProcesso = 100 / (size-1);
    int j = 1;
    int rankDest = 1;
    int i=1;
    int cont = 1;
    while(i<=100)
    {
      for(int j=0; j<quantidadeValoresProcesso;j++)
      {
        valor[0] = cont;
        MPI_Send(valor, 1, MPI_INT, rankDest, 0, MPI_COMM_WORLD);
        cont++;
      }
      valor[0] = -1;
      MPI_Send(valor, 1, MPI_INT, rankDest, 0, MPI_COMM_WORLD);

      i=i+quantidadeValoresProcesso;
      rankDest++;
    }
  }
  else
  {
    int valoresDivisiveis = 0;
    while(1)
    {
      MPI_Recv(valor, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, NULL);
      if(valor[0] == -1)
      {
        break;
      }
      if(valor[0] >= rank && ( valor[0] % rank == 0 ))
      {
        valoresDivisiveis++;
      }
    }
    printf("Meu rank é %d e recebi %d valores divisiveis por ele\n",rank,valoresDivisiveis);

  }

  MPI_Finalize();

  return 0;
}
