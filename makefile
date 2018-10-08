CC=gcc
CFLAGS=-I.
DEPS = child1.h
OBJ = main.o child1.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

run: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)