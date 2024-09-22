# Makefile inspired by Jacob Sorber's video: https://www.youtube.com/watch?v=CRlqU9XzVr4

CC = gcc
DEPFLAGS = -MP -MD
CFLAGS = -std=c99 -g $(DEPFLAGS)

BIN = simulator
SRC = src
OBJ = obj
SRCS = $(wildcard $(SRC)/*.c)
OBJS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

DEP = dep-files
DEPFILES = $(patsubst $(SRC)/%.c, %(DEP)/%.dep, $(SRCS))


.PHONY: all clean

all: $(BIN)

# Rule to create executable
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Rule to compile .c files to .o files
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to generate dependency files
$(DEP)/%.dep: %.c
	$(CC) -MM $< -MF $@ -MT $(@:.dep=.o)

# Include dependency files
-include $(DEPFILES)

clean:
	$(RM) -r $(BIN)