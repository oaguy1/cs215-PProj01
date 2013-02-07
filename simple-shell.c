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

FILE *history_file;
int h_count = 0;

int execute(char** argv){
    pid_t pid;
    int status;
    pid = fork();

    save_in_hist(argv); //temp spot saving twice

    if (pid < 0){
        printf("Your fork has failed you\n");
        return 1;
    } else if (pid == 0){
        if(execvp(argv[0], argv) < 0){
            printf("Your child has failed you\n");
            return 1;
	}
    } else if(!strcmp(argv[0], "exit") || !strcmp(argv[0], "quit")){
        printf("You have failed me for the last time commander\n");
        return 1;
    } else if(!strcmp(argv[0], "cd")) {
        if (chdir(argv[1]) == -1)
            printf("Error: chdir() has failed you");
    } else {
        while(wait(&status) != pid)
            ;// do nothing
    }
    
}

void save_in_hist(char** cmd){ 
       history_file = fopen("history.txt", "a"); 
       if (!history_file){
            printf("history read error"); 
       }
       fprintf (history_file, "%d %s\n", h_count++, cmd[0]);
       fclose(history_file);    
}
                                          
char*  get_from_hist(int num){//void for now 
       
	char* hist_cmd;

       history_file = fopen("history.txt", "r"); 
       if (!history_file){ 
            printf("history read error"); 
       }
       //get the right line
       //for (int i = 0; i <= num; i++){
       //		gets (hist_cmd, 100, history_file); 
       //}
       fclose(history_file); 
       return hist_cmd; 
} 

int main(void)
{
    char *cwd = NULL;
    char *temp = NULL;
    int should_run = 1;
    
    char *cmd[MAX_LINE];
    char input[MAX_LINE];
    
    //prime the history file
    history_file = fopen("history.txt", "w"); 

    if (!history_file){
	    printf("Error with history"); 
	    return 0; 
    }
   
    fclose(history_file); 

    while (should_run){
        // grab current working directory and print prompt
<<<<<<< HEAD
        cwd = getwd(cwd); 
=======
        cwd = getwd(cwd);
>>>>>>> Revert "more junk"
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
        
<<<<<<< HEAD
<<<<<<< HEAD
        execute(cmd);

<<<<<<< HEAD
        // flush *cmd so that it is completely empty,
        // prevents residual commands being passed
        memset(cmd, 0, sizeof(cmd));
=======
>>>>>>> Revert "I don't what I did"
=======
>>>>>>> Revert "Revert "I don't what I did""
        execute(cmd); 
<<<<<<< HEAD
=======
        }
        
        //remove the \n 
	//that gets added to the end
        int lcmd_len = (int) strlen(cmd[num_args]);
        cmd[num_args][lcmd_len-1] = '\0';
    	
        if(!strcmp(cmd[0], "exit") || !strcmp(cmd[0], "quit")){ 
        	printf("You have failed me for the last time commander\n"); 
		exit(0); 
	} else if (!strcmp(cmd[0], "!!")) { 
		execute(last_cmd()); 
		put_in_history(cmd); 
	} else if (!strcmp(cmd[0][0], "!")){ 
	        execute(cmd_num(cmd[0][1]));
		put_in_history(cmd); 	
	} else { 
		execute (cmd); 
		put_in_history(cmd);
	}	
>>>>>>> junk
>>>>>>> Revert "Revert "junk""
=======
>>>>>>> Revert "Revert "Revert "junk"""
=======
        if (execute(cmd) == 1){
            //exit
            return 1;
        }
>>>>>>> junk commit
    }//while
    
    return 0;
}

