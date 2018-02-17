/* Simple example of how to use MPI_Bcast.
 
   Sends an integer variable to everyone
 */
#include <mpi.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
        int val = 10, rank, size;
    
        MPI_Init(&argc,&argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        MPI_Comm_size(MPI_COMM_WORLD, &size);
    
        // only the master changes the value of val
    
        if(rank == 0) val = 20;
        
        printf("Process %d: value before Bcast: %d\n",rank, val);
    
        // master (0) sends val to everyone
        // all other have to execute this routine as well
    
        MPI_Bcast(&val, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
        printf("Process %d: value after Bcast: %d\n",rank, val);
        
        MPI_Finalize();
    
        return 0;
}