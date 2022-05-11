CC := gcc
CFLAGS := --std=c99 -Wall -Wextra -Wformat -pedantic

all: slow fast

hash.o:
	$(CC) $(CFLAGS) -o hash.o hash.c -c

slow: hash.o
	$(CC) $(CFLAGS) -o slow slow.c hash.o

fast: hash.o
	$(CC) $(CFLAGS) -o fast fast.c hash.o

fmt:
	clang-format -i --style=WebKit *.c *.h
