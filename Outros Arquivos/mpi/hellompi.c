#include <stdio.h>
#include <mpi.h>

int main(int argc, char **argv)
{
  int size;
  int rank;

  MPI_Init(&argc, &argv); // Ao contrário do fork, com MPI os processos são replicados desde o início da mainß
  MPI_Comm_rank(MPI_COMM_WORLD, &rank); //rank é o identificador de cada processo
  MPI_Comm_size(MPI_COMM_WORLD, &size); //size é o número de processos que eu tenho

  printf("Hello World, process %d of %d\n", rank, size);

  MPI_Finalize();

  return 0;
}
