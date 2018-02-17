/*
 Program that does nothing, just consume MEMORY. This program
 does not end.
 */

#include <stdio.h>
#include <stdlib.h>

#define MEMSIZE 100*1024*1024 // 100M

#define DEBUG 1

int main() {
    
    int count = 0;
    
    char *s = (char *) malloc(MEMSIZE);
    if (s == NULL) {
        printf("Error allocating memory\n");
        exit(1);
    }
    
    if (DEBUG) printf("MEM Dummy is executing (%d)\n",getpid());
    
    while (1) {
        int i=0;
        sleep(5);
        while (i<MEMSIZE) {
            s[i] = 'A';
            i++;
         }
        
        if (DEBUG)
            if (count++ % 10000)
                printf("%d: (MEM) I'm still alive.\n",getpid());

    }

}
