# Compiler and flags
CC = gcc
CFLAGS = -Wall -O0 -I../Part0 -I.

# Source files
SRCS = main.c matrix_ops.c ../Part0/tsc.c

# Output executable
TARGET = matrix.elf

# Default target
all: $(TARGET)

# Link the object files with optimization
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS) -lm

# Clean compiled files
clean:
	rm -f $(TARGET)
