#Jordan Bradshaw
#lab6

EXECUTABLE-L=spiritd
EXECUTABLE-T=mole
SRC-L=spiritd.c
SRC-T=mole.c
OBJ-L=spiritd.o
OBJ-T=mole.o

CC=gcc
CFLAGS=-g

all: $(EXECUTABLE-L) $(EXECUTABLE-T)


$(EXECUTABLE-L): $(SRC-L)
	$(CC) $(CFLAGS) -c $(SRC-L)
	$(CC) $(CFLAGS) -o $@ $(OBJ-L)

$(EXECUTABLE-T): $(SRC-T)
	$(CC) $(CFLAGS) -c $(SRC-T)
	$(CC) $(CFLAGS) -o $@ $(OBJ-T)

clean:
	rm -f $(EXECUTABLE-L) $(EXECUTABLE-T) $(OBJ-L) $(OBJ-T) *~
