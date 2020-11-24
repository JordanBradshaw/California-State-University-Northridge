#Jordan Bradshaw
#lab3 makefile

EXECUTABLE=catcher
SRC=main.c
OBJ=main.o

CC=gcc
CFLAGS=-g

all: $(EXECUTABLE)


$(EXECUTABLE): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

CLEAN:
	rm -f $(EXECUTABLE) $(OBJ) *~