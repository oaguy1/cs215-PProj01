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
#define MAX_SIZE		100 //number of cmds held in history.

//init history
char history[MAX_SIZE][MAX_LINE]; 
int history_count = 0;  

void execute(char** argv){ 
    pid_t pid;  
    int status; 
    pid = fork(); 

<<<<<<< HEAD
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

=======
   if (pid < 0){ 
   	printf("Your fork has failed you\n"); 
        exit(1); 
   } else if (pid == 0){
   	if(execvp(argv[0], argv) < 0){
        	printf("Your child has failed you\n");
	       exit(1); 	
	}
   } else { 
   	while(wait(&status) != pid)
		;
   } 
    
}

char* cmd_num(int num){ 
     //need some error handling
     return history[num];
} 

char* last_cmd(){ 
     return history[0]; 
} 

void put_in_history(char** a_cmd){ 
     if (history_count == 0){ 
     	strcpy(history[history_count++], a_cmd); 
     }  else if (history_count + 1 == MAX_SIZE){ 
     	//everything needs to be moved up
	int temp = history_count + 1; 
	while (temp != 0){	
		strcpy(history[temp--], history[temp]); 
	}
	//temp = 0;
	strcpy(history[temp], a_cmd); 
     }  else { 
     	fprintf(stderr, "Error: Array out of bounds)"); 
     }
>>>>>>> junk
} 

int main(void)
{
    char *cwd[FILENAME_MAX];
    char *temp = NULL;
    int should_run = 1;

    char *cmd[MAX_LINE];
    char input[MAX_LINE];

<<<<<<< HEAD
=======
   

>>>>>>> junk
    while (should_run){
        // grab current working directory and print prompt
        cwd = getwd(cwd);
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
<<<<<<< HEAD
        }//while

        //remove the \n that gets added to the end
        int lcmd_len = (int) strlen(cmd[num_args]);
        cmd[num_args][lcmd_len-1] = '\0';
<<<<<<< HEAD
        
=======



>>>>>>> Revert "I don't what I did"
        execute(cmd); 
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
    }//while

    return 0;
}

