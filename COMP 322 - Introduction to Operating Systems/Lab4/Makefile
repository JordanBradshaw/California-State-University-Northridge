IDIR = include
CC = gcc
CFLAGS = -I$(IDIR) -Wall -Wextra -g
LIBS = -pthread

OBJ = dining-p.o
SRC = dining-p.c
EXEC_NAME = dining-p 

all: $(OBJ) 
	$(CC) $(CFLAGS) -o $(EXEC_NAME) $(OBJ) $(LIBS)
	rm $(OBJ)

dining-p: $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC_NAME) $(OBJ) $(LIBS)
	rm $(OBJ)

dining-p.o: $(SRC)
	$(CC) $(CFLAGS) -g -c $(SRC)

clean:
	rm -f $(EXEC_NAME)
	rm -f $(OBJ)
	rm -f groupID.txt
