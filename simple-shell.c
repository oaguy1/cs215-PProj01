/**
 * Simple shell interface program.
 *
 * Operating System Concepts - Ninth Edition
 * Copyright John Wiley & Sons - 2013
 */

 /**
  * The steps are:                          
  * (1) parse the input to obtain the command and parameters
  * (2) invoke execvp() to start the process
  * (3) Obtain the output stream                       
  * (4) Output the contents returned by the command 
  */ 

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#define MAX_LINE		80  /* 80 chars per line, per command */

int main(void)
{
    char input[MAX_LINE];
    char cmd[MAX_LINE];
    char args[MAX_LINE];
    char temp[MAX_LINE];
    int should_run = 1;

    int i, upper;
    pid_t pid;

    while (should_run){   
        printf("jdcsh>");
        fflush(stdout);
        scanf("%s", input);
        pid = fork();

        strcpy(cmd, strtok(input, " "));
        printf("%s\n", input);
        i = 0;
        
        // parse command into tokens
        /*
        do {
            strcpy(strtok(NULL, " "), temp);
            strcat(args, temp);
            printf("%s\n", args);
        } while (temp != NULL);
        */

        // evaluate command
        if (pid < 0) { //error occured
            fprintf(stderr, "Fork failed\n");
            return 1;
        } else if(!strcmp(cmd, "exit")) {
            printf("You have failed me for the last time, commander!\n");
            return 0;
        } else if (pid == 0) {
            execvp(cmd, *args);
        } else {
            printf("I am the parent %d\n",pid);
	    wait(NULL);
        }
    }//while

    return 0;
}
