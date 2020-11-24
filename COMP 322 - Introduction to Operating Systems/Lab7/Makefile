#Jordan Bradshaw
#lab7

EXECUTABLE-L=matrix_add
EXECUTABLE-T=matrix_gen
SRC-L=matrix_add.c
SRC-T=matrix_gen.c
OBJ-L=matrix_add.o
OBJ-T=matrix_gen.o

CC=gcc
CFLAGS=-Wall -Wextra -g
LIB=-lrt 

all: $(EXECUTABLE-L) $(EXECUTABLE-T)


$(EXECUTABLE-L): $(SRC-L)
	$(CC) $(CFLAGS) -c $(SRC-L) $(LIB)
	$(CC) $(CFLAGS) -o $@ $(OBJ-L) $(LIB)

$(EXECUTABLE-T): $(SRC-T)
	$(CC) $(CFLAGS) -c $(SRC-T) $(LIB)
	$(CC) $(CFLAGS) -o $@ $(OBJ-T) $(LIB)

clean:
	rm -f $(EXECUTABLE-L) $(EXECUTABLE-T) $(OBJ-L) $(OBJ-T) *~
