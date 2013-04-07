# specify all source files here
SRC = history.c simple-shell.c

# specify target here (name of executable)
TARG = shell

# specify compiler, compile flags, and needed libs
CC = gcc
OPTS = -g -Wall
LIBS = -lm

# this translates .c files in src list to .o’s
OBJ = $(SRC:.c=.o)

# all is not really needed, but is used to generate the target
all: $(TARG)

# this generates the target executable
$(TARG): $(OBJ)
	$(CC) -o $(TARG) $(OBJ)

# this is a generic rule for .o files
%.o: %.c
	$(CC) $(OPTS) -c $< -o $@

# and finally, a clean line
clean:
	rm -f $(OBJ) $(TARG)
