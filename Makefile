# CHATGPT CODE. I honeslty don't understand it.

BIN := simulator
DEPDIR := dep-files
DEPFILES := $(addprefix $(DEPDIR)/, $(patsubst %.c,%.dep,$(wildcard *.c)))
OBJDIR := obj
OBJS := $(addprefix $(OBJDIR)/, $(patsubst %.c,%.o,$(wildcard *.c)))

CC := gcc
CFLAGS := -std=c99 -g

.PHONY: all clean

all: $(BIN)

# Rule to create executable
$(BIN): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Rule to compile .c files to .o files
$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to generate dependency files
$(DEPDIR)/%.dep: %.c
	@mkdir -p $(dir $@)
	$(CC) -MM $< -MF $@ -MT $(@:.dep=.o)

# Include dependency files
-include $(DEPFILES)

clean:
	$(RM) -r $(OBJDIR) $(DEPDIR)