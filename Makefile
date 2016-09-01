CC=clang
CFLAGS=-std=c11 -g

all:
	$(CC) $(CFLAGS) -o sort sort.c
