# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -pedantic

# Use cross compiler if on linux
ifeq ($(shell uname -s), Linux)
CC = x86_64-w64-mingw32-gcc
endif

# Target executable
TARGET = replundersco.exe

# Source files
SRCS = main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default target
all: $(TARGET)

# Linking step
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ 

# Compilation step
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
	rm $(OBJS) $(TARGET)
