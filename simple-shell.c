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
    char *temp = NULL;
    int should_run = 1;
    pid_t pid;
    char *cmd[MAX_LINE];
	char input[MAX_LINE];
    
    while (should_run){
        printf("jdcsh>");
        fflush(stdout);
        
        int num_args = 0;
        fgets(input, MAX_LINE, stdin);
        printf("\n"); //new line
        
        //Parse the input into cmd and argumentsi
        
        cmd[0] = strtok(input, " ");
        
        temp = strtok(NULL, " ");
        
        while (temp != NULL) {
            num_args++;
            cmd[num_args] = temp;
            temp = strtok(NULL, " ");
        }
        
        //remove the \n that gets added to the end
        int lcmd_len = (int) strlen(cmd[num_args]);
        cmd[num_args][lcmd_len-1] = '\0';
        
        pid = fork();
        
        // evaluate command
        if (pid < 0) {
            fprintf(stderr, "Your fork has failed you.\n");
            return 1; 
        } else if(!strcmp(cmd[0], "exit")) {
            printf("You have failed me for the last time, commander!\n");
            exit(0); 
        } else {
            //broken here we need to put in the file in argument 1.
            execvp(cmd[0], cmd);
        }
    }//while
    
    return 0;
}
