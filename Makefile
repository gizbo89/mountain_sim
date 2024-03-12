# Compiler
CC = g++
# Include paths
INCLUDES = -I$(PWD)
# Compiler flags
CFLAGS = -Wall -Wextra $(INCLUDES)

# Source files
SRCS := $(shell find . -type f -name '*.cpp')

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = myprogram

# Default target
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXEC)

# Rule to compile source files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -f $(OBJS) $(EXEC)

