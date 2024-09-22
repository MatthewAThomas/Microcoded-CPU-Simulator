# Makefile inspired by Jacob Sorber's video: https://www.youtube.com/watch?v=CRlqU9XzVr4

CC = gcc
CFLAGS = -std=c99 -g

BIN = simulator
SRC = src
OBJ = obj
SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))


.PHONY: all clean

all: $(BIN)

# Rule to create executable
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Rule to compile .c files to .o files
$(OBJ)/%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(BIN)