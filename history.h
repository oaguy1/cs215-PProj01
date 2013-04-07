/******************************************************************************
 * FILE: history.h
 * ---------------
 *  Code module to process shell history storage and retreval.
 *
 *  AUTHOR: Jasper Boyd and David N. Robinson
 *  DATE:   04/06/2013
 */

#ifndef HISTORY_MODULE
#define HISTORY_MODULE

/******************************************************************************
 * FUNCTION: init_history()
 * ------------------------
 *  Given a string that contains a file path, this function will properly set
 *  the module variables that allow this history_module to run properly. MUST
 *  BE RUN BEFORE CALLING ANY OTHER HISTORY COMMAND.
 */
void init_history(char* file_path);

/******************************************************************************
 * FUNCTION: reclaim_history_memory()
 * ----------------------------------
 *  Call this function to release all the memory dynamically allocated to the
 *  history module. ONLY CALL WHEN DONE USING THE HISTORY MODULE.
 */
void reclaim_history_memory();

/******************************************************************************
 * FUNCTION: view_hist()
 * ---------------------
 *  When executed, will print out all the previously executed commands from the
 *  shell history file. The history file is located in the home directory for
 *  the shell.
 */
void view_hist();

/******************************************************************************
 * FUNCTION: get_hist_count()
 * --------------------------
 *  Returns the current count of commands saved into history file
 */
int get_hist_count(); 

/******************************************************************************
 * FUNCTION: save_in_hist()
 * ------------------------
 *  Given a 2D character array containing a command and its arguments, an
 *  integer containing the number of arguments, as the current count of the
 *  commands kept in history, this function will save that command to the
 *  history file for later retrieval.
 */
int save_in_hist(char** cmd, int args);

/******************************************************************************
 * FUNCTION: get_from_hist()
 * -------------------------
 *  Given a number, this function will return a 2D character array constaining
 *  the command referenced by that number in the history file.
 */
char** get_from_hist(int num);

#endif
