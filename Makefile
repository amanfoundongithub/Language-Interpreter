# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g

# Final executable name
TARGET = interpreter

# Source files
SRCS = main.c ASTEvaluate.c ASTMake.c StringParser.c tokenizer.c

# Object files
OBJS = main.o ASTEvaluate.o ASTMake.o StringParser.o tokenizer.o

# Default target
all: $(TARGET)

# Link object files into the final executable.
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile main.c; adjust header dependencies as necessary.
main.o: main.c ASTEvaluate.h ASTMake.h ASTNode.h tokenType.h constants.h tokenizer.h StringParser.h
	$(CC) $(CFLAGS) -c main.c

# Compile ASTEvaluate.c.
ASTEvaluate.o: ASTEvaluate.c ASTEvaluate.h ASTNode.h tokenType.h constants.h
	$(CC) $(CFLAGS) -c ASTEvaluate.c

# Compile ASTMake.c.
ASTMake.o: ASTMake.c ASTMake.h ASTNode.h tokenizer.h constants.h tokenType.h
	$(CC) $(CFLAGS) -c ASTMake.c

# Compile StringParser.c.
StringParser.o: StringParser.c StringParser.h constants.h
	$(CC) $(CFLAGS) -c StringParser.c

# Compile tokenizer.c.
tokenizer.o: tokenizer.c tokenizer.h constants.h tokenType.h
	$(CC) $(CFLAGS) -c tokenizer.c

# Clean rule to remove generated files.
clean:
	rm -f $(OBJS) $(TARGET)
