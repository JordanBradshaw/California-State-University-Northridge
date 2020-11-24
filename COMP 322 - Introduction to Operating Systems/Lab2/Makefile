#Jordan Bradshaw
#lab2

EXECUTABLE-L=launch
EXECUTABLE-T=tube
SRC-L=launch.c
SRC-T=tube.c
OBJ-L=launch.o
OBJ-T=tube.o

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