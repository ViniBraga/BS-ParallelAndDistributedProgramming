#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>


#define TAMMSG 80


void criaProcesso(pid_t &pid);

int main(){

    int fd[2], nbytes, i = 0;

    pid_t pid1;
    pid_t pid2;

    char string[TAMMSG], buffer[TAMMSG];
    time_t begin_t, end_t;

    pipe(fd);
    criaProcesso(pid1);

    if(pid1 == 0){/*Codigo para o processo do filho*/
        
    }
    else{    /*Codigo para o processo do pai*/
    
        pipe(fd);
        criaProcesso(pid2);
        
    
    }
    return(0);

}

void criaProcesso(pid_t &pid){
    if((pid = fork()) == -1){
        printf("Erro ao criar processo = %d.\n", pid);
        return(1);    
    }
}