/** Server to sort an array of ints
**/


#include "vector.h"


void ordena(int a[]) {
    int i, j;
    
    for (i=0; i<MAX-1; i++)
        for (j=i; j<MAX; j++)
            if (a[i] > a[j]) {
                int aux = a[i];
                a[i] = a[j];
                a[j] = aux;
            }
    return;
    
}

int *sort_1_svc(int  *rec, struct svc_req *rqstp) {

    int i,j;
    
    ordena(rec);

    return rec;
}

