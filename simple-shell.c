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
char *hist_file_name = "/.history";
char *home_path;
FILE *history_file;
int h_count = 0;

void view_hist(){
    int i;
    char* temp;  
    history_file = fopen(home_path, "r");
    if (!history_file){
        printf("Could not open the history"); 
    }

    printf("\n"); 

    for (i = 0; i<=h_count; i++){
        fgets(temp, MAX_LINE, history_file);
        printf("%s\n", temp); 	
    }
}

int save_in_hist(char** cmd, int args, int count){ 
    int i; 

    history_file = fopen(home_path, "a"); 

    if (!history_file){
        printf("history read error"); 
    }

    printf("saving cmd: %s, to count: %d\n", cmd[0], count); 

    fprintf (history_file, "%d %s ", count, cmd[0]);

    for (i=1; i<=args; i++){
        fprintf (history_file, "%s ", cmd[i]); 
    }

    fprintf (history_file, "\n"); 
    fclose(history_file);
}

int get_from_hist(int num){ 
    printf("DECLARING VARIABLES");
    char* hist_cmd;
    char* cmd;
    char* temp;
    int num_args = 0;
    int i;

    history_file = fopen(home_path, "r"); 

    printf("IS THERE A FILE?!?!?!?!");
    if(!history_file) { 
        printf("History Read Error:\n");
        printf("Those who forget their history are doomed to repeat it...\n");
    }//if

    printf("I AM READING THE FILE!!!");
    //get the right line
    for (i = 0; i <= num; i++){
        fgets(hist_cmd, MAX_LINE, history_file);
        printf("hist_cmd: %s\n", hist_cmd); 
    }//for

    fclose(history_file); 
    printf("hist_cmd: %s\n", hist_cmd);

    //grab first token, command num, toss it
    strtok(hist_cmd, " ");

    //continue parsing command
    cmd[0] = strtok(NULL, " ");
    temp = strtok(NULL, " ");

    while (temp != NULL) {
        num_args++;
        cmd[num_args] = temp;
        temp = strtok(NULL, " ");
    }//while

    execute(cmd);
    return 0;
}

int execute(char** argv) { 
    pid_t pid;  
    int status;
    int exe_r;  
    pid = fork(); 

    //exit case
    if (!strcmp(argv[0], "exit") || !strcmp(argv[0], "quit")){
        exit(1); 
    }//if



    if (pid < 0){ 
        exit(1); 
    } else if (pid == 0){
        
        //change directory
        if (!strcmp(argv[0], "cd")){
            chdir(argv[1]);

        //repeat history command
        } else if (!strcmp(argv[0], "!!")){
            printf("run last command, command number %d \n", (h_count - 1));
            get_from_hist(h_count - 1);
            printf("WE GOT A LIVE ONE!");

        //show history command
        } else if (!strcmp(argv[0], "history")){
            view_hist();
        
        //execute command
        } else {  

            exe_r = execvp(argv[0], argv);
            if(exe_r < 0){
                exit(1); 	
            }//if

        }//if
    } else { 
        wait(&status);
        // while(wait(&status) != pid)
        // ;// do nothing
    }//if
}//execute

int main(void) {
    char *cwd = NULL;
    char *temp = NULL;
    int should_run = 1;
    int error;

    char *cmd[MAX_LINE];
    char input[MAX_LINE];

    //grabs current directory and sets it as 
    home_path = getwd(home_path);
    strcat(home_path, hist_file_name);
    printf("HISTORY FILE: %s\n", home_path);
    //clear history

    history_file = fopen(home_path, "w"); 
    if (!history_file){ 
        printf("history file could not open \n"); 
    }
    fclose(history_file); 

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

        save_in_hist(cmd, num_args, h_count); 

        execute(cmd);

        h_count++;

        // flush *cmd so that it is completely empty,
        // prevents residual commands being passed
        memset(cmd, 0, sizeof(cmd));
    }//while

    return 0;
}//main
