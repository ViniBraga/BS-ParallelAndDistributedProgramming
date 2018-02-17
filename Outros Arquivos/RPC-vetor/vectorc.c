
/** Simple client to a sorting server
**/


#include <stdio.h>
#include <rpc/rpc.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

main(int argc, char *argv[]) {

    CLIENT *cl;
    vetor v;
    vetor *answer;
    int i;
    
    v.vetor_len = MAX;
    v.vetor_val = malloc(MAX*sizeof(int));
    
    for (i=0; i<MAX; i++) v.vetor_val[i] = MAX - i;
    
    if (argc != 2) {
        printf("Usage: %s server\n", argv[0]); 
        return (1); 
    } 

    if (!(cl = clnt_create(argv[1], SORTPROG,SORTVERS,"tcp"))) {
        clnt_pcreateerror(argv[1]); 
        return(1); 
    } 

    /** sort remoto **/

    answer = (vetor *) sort_1(&v,cl);

    if (answer == (vetor *) NULL) {
        fprintf(stderr,"Error: could not produce meaningful results"); 
        return(1); 
    }

    for (i=0; i<MAX; i++) printf("%d:%d ", v.vetor_val[i], answer->vetor_val[i]);
    printf("\n");
   
    return (0);
} 
