/***************************************************************************
 *
 * PROGRAMA EXEMPLO PIPELINE USANDO MPI
 *
 * FUNCIONAMENTO: PROGRAMA EXEMPLO DE UM PIPE CIRCULAR COM N ESTAGIOS ONDE 
 * N EH O NUMERO DE PROCESSOS MPI ATIVOS. O ESTAGIO "0" DO PIPE VAI GERANDO 
 * INTEIROS E ENVIANDO PARA O ESTAGIO SEGUINTE. CADA INTEIRO DEVE FAZER A 
 * VOLTA INTEIRA NO PIPE E VOLTAR AO ESTAGIO "0". NESTE EXEMPLO, SAO 
 * INTRODUZIDOS DEZ VALORES INTEIROS NO PIPE.
 *
 * NOTA: NESTE EXEMPLO AS PRIMITIVAS DE COMUNICACAO SAO BLOQUEANTES, O QUE 
 * DIMINUI CONSIDERAVELMENTE O PARALELISMO DESTA IMPLEMENTACAO.
 *
 * OBS: FUNCIONA CORRETAMENTE COM NO MINIMO DOIS PROCESSOS MPI
 * ***********************************************************************/

#include "mpi.h"
#include <stdio.h>

#define NUM_INTS	10
#define FIRST		 0          /* taskid of first process */

int main(int argc,char **argv)
{
    int	ntasks,                    /* total number of MPI tasks in partitiion */
    nstages,                      /* number of worker tasks */
    taskid,	                       /* task identifier */
    rc,                            /* return error code */
    dest,                          /* destination task id to send message */
    i,                             /* loop variable */
    indexmsg = 1,                  /* setting a message type */
    source,                        /* origin task id of message */
    current_int;                   /* the int being currently used */
    
    MPI_Status status;


/*************************** initialization **********************************/

    rc = MPI_Init(&argc,&argv);
    rc|= MPI_Comm_size(MPI_COMM_WORLD,&ntasks);
    rc|= MPI_Comm_rank(MPI_COMM_WORLD,&taskid);

    if (rc != MPI_SUCCESS) {
       printf ("Error initializing MPI and obtaining task ID information\n");
       exit(1);
    }
    else
    {  
       printf("%d MPI tasks, I am task ID %d\n", ntasks, taskid);
       fflush(stdout);
    }
    
    nstages = ntasks-1;

    MPI_Barrier(MPI_COMM_WORLD);

/**************************** First stage of the pipe **************************/
    
    if (taskid == FIRST)
    { 

        dest = taskid+1;

	    printf("--------------------------------------------------\n");
        for(i=0; i<NUM_INTS; i++) 
        {
            current_int = i;
            printf("I am pipe stage %d sending %d to pipe stage %d \n",taskid, current_int, dest);
            
            MPI_Send(&current_int, 1, MPI_INT, dest, indexmsg, MPI_COMM_WORLD);
        }
        
        // Now wait to receive back the results from the last pipe stage for each int and print 
        printf("--------------------------------------------------\n"); 
	    for (i=1; i<= NUM_INTS; i++)
        {   
            MPI_Recv(&current_int, 1, MPI_INT, nstages, indexmsg, MPI_COMM_WORLD, &status);
            printf("I am pipe stage %d receiving %d from pipe stage %d\n", taskid, current_int, status.MPI_SOURCE);
            fflush(stdout);
        }
        printf("FIRST PIPE STAGE: All Done! \n");
	    fflush(stdout);
    }

/**************************** stage task ************************************/

   if (taskid > FIRST)
   {
	    source = taskid-1;  

	    printf("--------------------------------------------------\n");
        for(i=0; i<NUM_INTS; i++) 
        {            
         
            MPI_Recv(&current_int, 1, MPI_INT, source, indexmsg, MPI_COMM_WORLD, &status);
            
            
            printf("Pipe stage %d received %d, sending to %d\n",taskid, current_int, taskid+1);
            
            if (taskid == nstages) // ultimo do pipe, envia para o primeiro
            {
                MPI_Send(&current_int, 1, MPI_INT, FIRST, indexmsg, MPI_COMM_WORLD);
            }
            else // envia para o proximo
            {
                MPI_Send(&current_int, 1, MPI_INT, taskid+1, indexmsg, MPI_COMM_WORLD);
            }
        }
 
   }
   MPI_Finalize();
}
//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
