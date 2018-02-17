/** Server to sort an array of ints
**/


#include "vector.h"


void ordena(int a[],int size) {
    int i, j;
    
    for (i=0; i<size-1; i++)
        for (j=i; j<size; j++)
            if (a[i] > a[j]) {
                int aux = a[i];
                a[i] = a[j];
                a[j] = aux;
            }
    return;
    
}

vetor *sort_1_svc(vetor  *rec, struct svc_req *rqstp) {

    int i,j;
    
    ordena(rec->vetor_val, rec->vetor_len);

    return rec;
}

