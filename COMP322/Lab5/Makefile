#Jordan Bradshaw
#lab5
EXECUTABLES=pageOffset
SRC=pageOffset.c
OBJ=pageOffset.o


CC=gcc
CFLAGS=-g

all: $(EXECUTABLES)


$(EXECUTABLES): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(CFLAGS) -o $@ $(OBJ)


clean:
	rm -f $(EXECUTABLES) $(OBJ) *~
