CC = gcc
DEPFLAGS = -MMD -MP -g

BINARY = test-loader

CFILES = $(wildcard *.c)
CFILES += ../loader.c

OBJECTS = $(patsubst %.c, %.o, $(CFILES))

DEPFILES = $(patsubst %.c, %.d, $(CFILES))
CFLAGS = -std=c99 -g

.PHONY: all clean

all: $(BINARY)

# Includes dependency files: tells make to recompile if a change is made to a header file
# THE INCLUDE STATEMENT MUST BE AFTER THE 'all' TARGET (not sure why though...)
-include $(DEPFILES)
# The '-' in '-include' is so that make doesn't complain if the %.d files don't exist yet

# not sure if CFLAGS is added correctly
$(BINARY): $(OBJECTS) 
	$(CC) $(CFLAGS) $^ -o $(BINARY)

# '$<' tells make to only compile the first dependency (%.c, not Makefile)
%.o: %.c Makefile
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

clean:
	rm -rf $(BINARY) $(OBJECTS) $(DEPFILES)