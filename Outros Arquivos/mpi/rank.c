#include <mpi.h>
#include <stdio.h>

int main(int argc, char **argv) {
  int rank,size;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0) {
     printf("I'm rank 0!\n");
  } else {
      printf("(%d/%d) -> This is my rank\n",rank,size);
  }
  MPI_Finalize();
  return 0;
}