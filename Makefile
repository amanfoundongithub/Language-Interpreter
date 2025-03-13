CC = gcc
CFLAGS = -Wall -g

# Object files
OBJS = main.o tokenizer.o ASTMake.o

# Targets
all: interpreter

interpreter: $(OBJS)
	$(CC) $(CFLAGS) -o interpreter $(OBJS)

main.o: main.c ASTNode.h ASTMake.h tokenizer.h constants.h tokenType.h
	$(CC) $(CFLAGS) -c main.c

tokenizer.o: tokenizer.c tokenizer.h constants.h tokenType.h
	$(CC) $(CFLAGS) -c tokenizer.c

ASTMake.o: ASTMake.c ASTMake.h ASTNode.h
	$(CC) $(CFLAGS) -c ASTMake.c

clean:
	rm -f *.o interpreter
