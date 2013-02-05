cs215-PProj01
=============

##Jasper Boyd and David Robinson

### Overview: 

The Project consists of 3 parts. 

#### Part 1: Creating the external process and executing the command in that process. 
##### Status: Implemented.

	1. Parse command for parameters.
		-strtok (string.h) 
	2. These parameters than need to be passed to the C equivalent of 'ProcessBuilder'(java).
	3. Execute the process.  

#### Part 2: Modifying the shell to changing directories.

##### Status: In-Progress.

	**Works**
        * Support for 'cd' command with absolute paths
        
        **Needs Work**
        * Support for relative paths

#### Part 3: Adding a history feature.

##### Status: Needs-to-be-Implemented.   

	1. Enter commands into history.
	2. Enter support for the command history (with the command numbers). 
	3. When the user enters "!!" run the previous command in history. 
	4. When the user enter "!<integer value i>".
