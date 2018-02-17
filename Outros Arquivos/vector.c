/* Simple example of how to send vectors to several slaves.

 */
#include <mpi.h>
#include <stdio.h>
#include <math.h>

#define MAXSIZE 12

void generate_vector(int a[]) {
    int i;
    
    for (i=0; i<MAXSIZE; i++)
        a[i] = i;
    
}



int main(int argc, char **argv) {
    int rank, np, tag=0, i;
    MPI_Status status;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    
    int nelems = MAXSIZE/(np-1);
    
    if (rank == 0) {
        int a[MAXSIZE];
        generate_vector(a);
        for (i=1; i<np; i++)
             MPI_Send(a+(i-1)*nelems, nelems, MPI_INT, i, tag, MPI_COMM_WORLD);
            
         printf("Vetores enviados.\n");
    }
    else {
        int b[nelems];
        
        MPI_Recv(b, nelems, MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
        
        printf("\n");
        for (i=0; i<nelems; i++)
            printf("Processo %d recebeu valor b[%d] = %d \n",rank,i,b[i]);
        
    }
    
    MPI_Finalize();
    return 0;
}