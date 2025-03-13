CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

TARGET = interpreter

# Source files.
SRCS = main.c ASTEvaluate.c ASTMake.c tokenizer.c

# Object files.
OBJS = main.o ASTEvaluate.o ASTMake.o tokenizer.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c ASTEvaluate.h ASTMake.h ASTNode.h tokenType.h constants.h tokenizer.h
	$(CC) $(CFLAGS) -c main.c

ASTEvaluate.o: ASTEvaluate.c ASTEvaluate.h ASTNode.h tokenType.h constants.h
	$(CC) $(CFLAGS) -c ASTEvaluate.c

ASTMake.o: ASTMake.c ASTMake.h ASTNode.h
	$(CC) $(CFLAGS) -c ASTMake.c

tokenizer.o: tokenizer.c tokenizer.h constants.h tokenType.h
	$(CC) $(CFLAGS) -c tokenizer.c

clean:
	rm -f $(OBJS) $(TARGET)
