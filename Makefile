
# Makefile

CC = gcc
CFLAGS = -Wall
DEPS = window.h
OBJ = display.o window.o

LDFLAGS=-lncurses

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

display: $(OBJ)
	gcc $(CFLAGS) $(LDFLAGS) -o $@ $^
