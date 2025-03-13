CC = gcc
CFLAGS = -Wall -Wextra -std=c99

all: interpreter

interpreter: main.o tokenizer.o
	$(CC) $(CFLAGS) -o interpreter main.o tokenizer.o

main.o: main.c tokenizer.h
	$(CC) $(CFLAGS) -c main.c

tokenizer.o: tokenizer.c tokenizer.h
	$(CC) $(CFLAGS) -c tokenizer.c

clean:
	rm -f *.o interpreter
