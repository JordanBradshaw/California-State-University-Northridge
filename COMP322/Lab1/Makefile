#Jordan Bradshaw
#lab1

#this is my makefile for my lab assignment, that allows me to easily and accurately rebuild the
#lab assignment.

# EXECUTABLES is a Make Variable (similar to an environment variable) that lists all the
# "executables" associated with the lab. 
EXECUTABLES=time-4-baby-and-me
SRC=main.c
OBJ=main.o

# The CC and CFLAGS variables are defined to ensure I'm using the native compiler and
# # that the correct command-line options are set

CC=gcc
CFLAGS=-g

# Here is my default target for the Makefile.  When I type make, this first target will
# # be created. I.e., all the executables

all: $(EXECUTABLES)

# On the following lines (which _must_ start with a tab), are the commands I need to type -- 
# # each time my source file is modified.

$(EXECUTABLES): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

# By convention, I always have a target called
# # "clean" that I used to define all temporary
# # or intermediates.

clean:
	rm -f $(EXECUTABLES) $(OBJ) *~
