# Makefile for compiling filter program

# Compiler and flags
CC = gcc
CFLAGS = -ggdb3 -gdwarf-4 -O0 -std=c11 -Wall -Werror -Wextra -Wno-sign-compare -Wno-unused-parameter -Wno-unused-variable -Wshadow
LDFLAGS = -lm

# Source files
SRCS = filter.c helpers.c
# Output executable
TARGET = filter

# Build target
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# Clean up
clean:
	del $(TARGET).exe 2>nul || rm -f $(TARGET)
