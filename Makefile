# Compiler to use
CXX = g++

# Directory where the source files are located
SRC_DIR = src

# Compiler flags
CXXFLAGS = -I$(SRC_DIR) -Wall -Wextra -std=c++17

# Source files
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/bus/bus.cpp $(SRC_DIR)/cpu/cpu.cpp $(SRC_DIR)/ram/ram.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
EXEC = program

# Default rule
all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $(EXEC)

# Rule to build object files
.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up the build
clean:
	rm -f $(OBJS) $(EXEC)

