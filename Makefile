
# Makefile

CC = gcc
CFLAGS = -Wall
DEPS = window.h
OBJ = main.o display.o window.o

LDFLAGS=-lncurses

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

main: $(OBJ)
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm $(OBJ)
