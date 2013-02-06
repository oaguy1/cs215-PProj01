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

void execute(char** argv){
    pid_t pid;
    int status;
    pid = fork();
    
    if (pid < 0){
        printf("Your fork has failed you\n");
        exit(1);
    } else if (pid == 0){
        if(execvp(argv[0], argv) < 0){
            printf("Your child has failed you\n");
            exit(1);
        }
    } else if(!strcmp(argv[0], "exit") || !strcmp(argv[0], "quit")){
        printf("You have failed me for the last time commander\n");
        exit(0);
    } else if(!strcmp(argv[0], "cd")) {
        chdir(argv[1]);
    } else {
        while(wait(&status) != pid)
            ;// do nothing
    }
    
}

int main(void)
{
    char *cwd = NULL;
    char *temp = NULL;
    int should_run = 1;
    
    char *cmd[MAX_LINE];
    char input[MAX_LINE];
    
    while (should_run){
        // grab current working directory and print prompt
        getwd(cwd);
        printf("jdcsh: %s>", cwd);
        fflush(stdout);
        
        int num_args = 0;
        fgets(input, MAX_LINE, stdin);
        printf("\n"); //new line
        
        //Parse the input into cmd and arguments
        cmd[0] = strtok(input, " ");
        temp = strtok(NULL, " ");
        
        while (temp != NULL) {
            num_args++;
            cmd[num_args] = temp;
            temp = strtok(NULL, " ");
        }//while
        
        //remove the \n that gets added to the end
        int lcmd_len = (int) strlen(cmd[num_args]);
        cmd[num_args][lcmd_len-1] = '\0';
        
        
        
        execute(cmd); 
    }//while
    
    return 0;
}

