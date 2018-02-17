/*
   Program that does nothing, just consume CPU time. This program
   does not end.
 */

#include <stdio.h>

#define DEBUG 1

int main() {

    int count = 0;
    if (DEBUG) printf("CPU Dummy is executing (%d)\n",getpid());
    while (1) {
        // Use CPU time
        int i = 1000000;
        while (i--);
        
        if (DEBUG)
            if (count++ % 10000)
              printf("%d: (CPU) I'm still alive.\n",getpid());
    }

}
