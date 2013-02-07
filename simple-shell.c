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

//Global Variable
FILE *history_file;
int h_count = 0;

void save_in_hist(char** cmd){ 
    history_file = fopen("history.txt", "a"); 
    if (!history_file){
        printf("history read error"); 
    }
    fprintf (history_file, "%d %s\n", h_count++, cmd[0]);
    fclose(history_file);    
}

char* get_from_hist(int num){//void for now 
    char* hist_cmd;
    int i;

    history_file = fopen("history.txt", "r"); 
    
    if(!history_file) { 
        printf("History Read Error:\n");
        printf("Those who forget their history are doomed to repeat it...\n");
    }//if

    //get the right line
    for (i = 0; i <= num; i++){
        fgets(hist_cmd, MAX_LINE, history_file);
    }//for

    fclose(history_file); 
    return hist_cmd; 
}

int execute(char** argv) { 
    pid_t pid;  
    int status; 
    pid = fork(); 

    if (pid < 0){ 
        exit(1); 
    } else if (pid == 0){
        if(execvp(argv[0], argv) < 0){
            exit(1); 	
        }//if
    } else if(!strcmp(argv[0], "exit") || !strcmp(argv[0], "quit")){ 
        exit(1); 
    } else if(!strcmp(argv[0], "cd")) {
        chdir(argv[1]);
    } else { 
        while(wait(&status) != pid)
            ;// do nothing
    }//if
}//execute

int main(void) {
    char *cwd = NULL;
    char *temp = NULL;
    int should_run = 1;
    int error;

    char *cmd[MAX_LINE];
    char input[MAX_LINE];

    while (should_run){
        // grab current working directory and print prompt
        cwd = getwd(cwd); 
        printf("jdcsh: %s>", cwd);
        fflush(stdout);

        int num_args = 0;
        fgets(input, MAX_LINE, stdin);

        // parse the input into cmd and arguments
        cmd[0] = strtok(input, " ");
        temp = strtok(NULL, " ");

        while (temp != NULL) {
            num_args++;
            cmd[num_args] = temp;
            temp = strtok(NULL, " ");
        }//while

        // remove the \n that gets added to the end
        int lcmd_len = (int) strlen(cmd[num_args]);
        cmd[num_args][lcmd_len-1] = '\0';

        error = execute(cmd);

        // flush *cmd so that it is completely empty,
        // prevents residual commands being passed
        memset(cmd, 0, sizeof(cmd));
    }//while

    return 0;
}//main

