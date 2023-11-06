# Compiler to be used
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17 -Isrc/include

# Source directories
SRC_DIRS = src src/circuit src/components src/sources src/sources/AC src/sources/DC src/simulator src/test

# Automatically find all the source files in the specified source directories
SOURCES = $(shell find $(SRC_DIRS) -name *.cpp)

# List of object files, placed in the obj directory
OBJ_DIR = obj
OBJECTS = $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)

# The final executable name
BIN_DIR = bin
EXECUTABLE = $(BIN_DIR)/circuit_simulator

# Default target
all: directories $(EXECUTABLE)

# Create the necessary directories
directories:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Compiling each source file to an object file
$(OBJ_DIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Linking the object files to produce the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ -o $@

# Clean target
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets
.PHONY: all clean directories
