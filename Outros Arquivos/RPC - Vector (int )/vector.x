/** 
    Author: Avelino F. Zorzo
    avelino.zorzo@pucrs.br

    Date: 06.11.2014
    
   This code will be translated into the needed stubs and headers
   Use: rpcgen vector.x

**/


const MAX = 100;

typedef int vetor[MAX];	

program SORTPROG {                /* value to register the program */
    version SORTVERS {            /* version must be assigned a value */
        vetor SORT(vetor) = 1;     /* this is a service function */
    } =1;                          /* version value */
} = 0x20000005;                    /* program value */   
