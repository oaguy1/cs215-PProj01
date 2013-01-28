/**
 * Simple shell interface program.
 *
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>



#define MAX_LINE		80 /* 80 chars per line, per command */

int main(void)
{
    char *args[MAX_LINE/2 + 1];	/* command line (of 80) has max of 40 arguments */
    char cmd[20];      //temp variable until we can properly deal with args
    int should_run = 1;

    int i, upper;
    pid_t pid;

    while (should_run){   
        printf("osh>");
        fflush(stdout);
        scanf("%s", cmd);
        pid = fork();

        if (pid < 0) { //error occured
            fprintf(stderr, "Fork failed\n");
            return 1;
        } else if (pid == 0) {
            execvp(cmd, args);
        } else {
            printf("I am the parent %d\n",pid);
	    wait(NULL);
        }

        /**
         * The steps are:                          
         * (1) parse the input to obtain the command and parameters
         * (2) invoke execvp() to start the process
         * (3) Obtain the output stream                       
	 * (4) Output the contents returned by the command 
         */
    }//while

    return 0;
}
