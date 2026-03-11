# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra

# Executable name
TARGET = voting

# Source file
SRC = voting_system.c

# Default target
all: $(TARGET)

# Compile program
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Clean compiled files
clean:
	rm -f $(TARGET) *.o *.dat