/**
 * The steps are:
 * (1) parse the input to obtain the command and parameters
 * (2) invoke execvp() to start the process
 * (3) Obtain the output stream
 * (4) Output the contents returned by the command
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

#include "history.h"

#ifndef MAX_LINE
#define MAX_LINE		80  /* 80 chars per line, per command */
#endif

//Global Variable
int num_args = 0;
char *home_path;
char ** cmd;

//get_from_hist

int  execute(char** argv) { 
    int status;
    int exe_r;
    pid_t pid = fork(); 

    printf("The PID is %d\n", pid);

    //exit case
    if (!strcmp(argv[0], "exit") || !strcmp(argv[0], "quit")){
        return 1; 
    }//if

    if (pid < 0){
        printf("There was an error with not enough memory\n");
        return 1; 
    } else if (pid == 0){

        printf("I am the child! PID %d\n", pid);

        //change directory
        if (!strcmp(argv[0], "cd")){
            printf("Changing directory to %s\n", argv[1]);
            chdir(argv[1]);

        //show history command
        } else if (!strcmp(argv[0], "history")){
            printf("Viewing history!");
            view_hist();

        //execute command
        } else {

            printf("Executing command: %s\n", argv[0]);
            exe_r = execvp(argv[0], argv);
            if(exe_r < 0){
                return 1; 	
            }//if

        }//if
    } else {
        printf("I am the parent! PID %d\n", pid);
        wait(&status);
        // ;// do nothing
    }//if

    return 0;
}//execute

char** parse(char* input) {
    char *temp = NULL;

    strcpy(cmd[0], strtok(input, " "));
    temp = strtok(NULL, " ");

    while (temp != NULL) {
        num_args++;
        strcpy(cmd[num_args], temp);
        temp = strtok(NULL, " ");
    }//while

    return cmd;
}//parse

int main(void) {
    char *cwd = NULL;
    int should_run = 1;
    int history_cmd;
    int i;
    char input[MAX_LINE];
     
    cmd = (char **) malloc(MAX_LINE*sizeof(char *));
    for(i = 0; i < MAX_LINE; i++) {
        cmd[i] = (char *) malloc(MAX_LINE*sizeof(char));
    }//for

    //grabs current directory and sets it as home directory
    home_path = getwd(home_path);
    strcat(home_path, "/.history");
    init_history(home_path);

    while (should_run){
        // grab current working directory and print prompt
        cwd = getwd(cwd); 
        printf("jdcsh: %s>", cwd);
        fflush(stdout);

        fgets(input, MAX_LINE, stdin);

        memcpy(cmd , parse(input), sizeof(cmd));

        // remove the \n that gets added to the end
        int lcmd_len = (int) strlen(cmd[num_args]);
        cmd[num_args][lcmd_len-1] = '\0';

        // if cmd is a history command, replace cmd with proper command from
        // history file 
        if(!strcmp(cmd, "!!")) {
            memcpy(cmd, get_from_hist(get_hist_count() - 1), sizeof(cmd));
        } else if(cmd[0][0] == '!') {
            history_cmd = atoi(cmd[0] + 1);
            memcpy(cmd, get_from_hist(history_cmd), sizeof(cmd));
        }//if

        save_in_hist(cmd, num_args);

        should_run = !execute(cmd);

        // flush cmd so that it is completely empty,
        // prevents residual commands being passed
        for(i = 0; i < MAX_LINE; i++) {
            memset(cmd[i], '\0', MAX_LINE);
        }//for
    }//while


    return 0;
}//main
