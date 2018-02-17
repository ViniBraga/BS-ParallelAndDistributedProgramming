/** Simple set of functions for a server calculator using rpcgen
**/


#include "calc.h"

/** if you want to have some state in the server, uncomment the following line **/

   int num_calls_add = 0; 

int *add_args_1_svc(record *rec, struct svc_req *rqstp) {

    static int result;

    result = rec->first_num + rec->second_num;

    num_calls_add++;

    return &result;
}

int *sub_args_1_svc(record *rec, struct svc_req *rqstp) {

    static int result;

    result = rec->first_num - rec->second_num;

    return &result;
}

int *state_1_svc(void *pvoid, struct svc_req *rqstp) {

    return &num_calls_add;
}

