/******************************************************************************
 * FILE: history.c
 * ---------------
 *  Code module to process shell history storage and retreval.
 *
 *  AUTHOR: Jasper Boyd and David N. Robinson
 *  DATE:   04/06/2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "history.h"

#ifndef MAX_LINE
#define MAX_LINE		80  /* 80 chars per line, per command */
#endif

// Global Variables
char *history_file_path;
FILE *history_file;
char ** cmd;
int h_count;

/******************************************************************************
 * FUNCTION: init_history()
 * ------------------------
 *  Given a string that contains a file path, this function will properly set
 *  the module variables that allow this history_module to run properly. MUST
 *  BE RUN BEFORE CALLING ANY OTHER HISTORY COMMAND.
 */
void init_history(char* file_path) {
    int i;

    history_file_path = (char *) malloc(MAX_LINE*sizeof(char));
    strcpy(history_file_path, file_path);
    h_count = 0;

    // clear history file of previous contents
    history_file = fopen(history_file_path, "w"); 
    if (!history_file){ 
        fprintf(stderr, "history file could not open\n"); 
    }//if
    fclose(history_file); 

    // initialize command array, used for retrieveing and parsing commands from
    // history
    cmd = (char **) malloc(MAX_LINE*sizeof(char *));
    for(i = 0; i < MAX_LINE; i++) {
        cmd[i] = (char *) malloc(MAX_LINE*sizeof(char));
    }//for
}//init_history

/******************************************************************************
 * FUNCTION: reclaim_history_memory()
 * ----------------------------------
 *  Call this function to release all the memory dynamically allocated to the
 *  history module. ONLY CALL WHEN DONE USING THE HISTORY MODULE.
 */
void reclaim_history_memory() {
   int i;

   for(i = 0; i < MAX_LINE; i++) {
        free(cmd[i]);
        cmd[i] = NULL;
    }//for
    free(cmd);
    cmd = NULL; 

}//reclaim_history_memory

/******************************************************************************
 * FUNCTION: view_hist()
 * ---------------------
 *  When executed, will print out all the previously executed commands from the
 *  shell history file. The history file is located in the home directory for
 *  the shell.
 */
void view_hist() {
    int i;
    char* temp;  
    history_file = fopen(history_file_path, "r");
    if (!history_file){
        printf("Could not open the history"); 
    }//if

    printf("\n");

    for (i = 0; i<=h_count; i++){
        fgets(temp, MAX_LINE, history_file);
        printf("%s\n", temp); 	
    }//for
}//view_hist

/******************************************************************************
 * FUNCTION: save_in_hist()
 * ------------------------
 *  Given a 2D character array containing a command and its arguments, an
 *  integer containing the number of arguments, as the current count of the
 *  commands kept in history, this function will save that command to the
 *  history file for later retrieval.
 */
int save_in_hist(char** cmd, int args) { 
    int i; 

    history_file = fopen(history_file_path, "a"); 

    if (!history_file){
        printf("history read error");
        return 1;
    }//if

    fprintf (history_file, "%d %s ", h_count, cmd[0]);

    for (i=1; i<=args; i++){
        fprintf (history_file, "%s ", cmd[i]); 
    }//for

    fprintf (history_file, "\n"); 
    fclose(history_file);

    h_count++;

    return 0;
}//save_in_hist

/******************************************************************************
 * FUNCTION: get_hist_count()
 * --------------------------
 *  Returns the current count of commands saved into history file
 */
int get_hist_count() {
    return h_count;
}//get_hist_count

/******************************************************************************
 * FUNCTION: get_from_hist()
 * -------------------------
 *  Given a number, this function will return a 2D character array constaining
 *  the command referenced by that number in the history file.
 */
char** get_from_hist(int num) { 
    char* hist_cmd;
    char* temp;
    int num_args = 0;
    int i;
      
    history_file = fopen(history_file_path, "r"); 

    if(!history_file) { 
        printf("History Read Error:\n");
        printf("Those who forget their history are doomed to repeat it...\n");
    }//if

    //get the right line
    for (i = 0; i <= num; i++){
        fgets(hist_cmd, MAX_LINE, history_file);
    }//for

    fclose(history_file); 

    //grab first token, command num, toss it
    strtok(hist_cmd, " ");

    //continue parsing command 
    strcpy(cmd[0], strtok(NULL, " "));
    temp = strtok(NULL, " ");

    while (temp != NULL) {
        num_args++;
        strcpy(cmd[num_args], temp);
        temp = strtok(NULL, " ");
    }//while

    return cmd;
}//get_from_hist
