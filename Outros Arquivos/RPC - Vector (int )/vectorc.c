
/** Simple client to a sorting server
**/


#include <stdio.h>
#include <rpc/rpc.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

main(int argc, char *argv[]) {

    int v[MAX];
    int *answer;
    int i,j;
    int nservers = argc - 1;
    CLIENT *cl[nservers];

    for (i=0; i<MAX; i++) v[i] = MAX - i;
    
    for (i=0; i<nservers; i++) {
        if (!(cl[i] = clnt_create(argv[i+1], SORTPROG,SORTVERS,"tcp"))) {
            clnt_pcreateerror(argv[i+1]);
            return(1);
        }
    }

    for (i=0; i<nservers; i++) {
        /** sort remoto **/

        answer = (int *) sort_1(v,cl[i]);

        if (answer == (int *) NULL) {
            fprintf(stderr,"Error: could not produce meaningful results");
            return(1); 
        }

        for (j=0; j<MAX; j++) printf("%d:%d ", v[j], answer[j]);
        printf("\n\n");
    }
   
    return (0);
} 
