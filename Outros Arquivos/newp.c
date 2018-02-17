/*
 Program that does waits for the name of a program to be executed.
 It forks a new process and then executes that command over the 
 forked process using the execv system call.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

int main() {

    char command[80];

    printf("Command :");
    gets(command);        // this should be avoided
    printf("\n");
    while (1) { // do it forever
      
      pid_t pid;

      // creates a new process to execute the given command
      pid = fork();
      if (pid == 0) {
          int ret = setpriority(PRIO_PROCESS,PRIO_PROCESS,8); // set priority to 8
          printf("I will execute %s with priority %d\n", command,prio);
          printf("%d\n",execv(command,NULL));
      }
        
      printf("Command :");
      gets(command);  // this should be avoided

      printf("\n");
   }

}
