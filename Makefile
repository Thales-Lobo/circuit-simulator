# Compiler to be used
CXX = g++

# Compiler flags
# -Wall: Turn on most compiler warnings
# -Wextra: Turn on more compiler warnings
# -std=c++11: Use the C++11 standard
CXXFLAGS = -Wall -Wextra -std=c++11

# List of source files
SOURCES = ACVoltageSource.cpp \
          ACCurrentSource.cpp \
          Resistor.cpp \
          Inductor.cpp \
		  Capacitor.cpp \
          Mesh.cpp \
          Circuit.cpp \
          Simulator.cpp \
          main.cpp

# List of object files generated from source files
OBJ_DIR = obj
OBJECTS	= $(addprefix $(OBJ_DIR)/, $(SOURCES:.cpp=.o))

# The final executable name
BIN_DIR		= bin
EXECUTABLE	= $(BIN_DIR)/circuit_simulator

# Default target to be executed when you run 'make'
all: directories $(EXECUTABLE)

# Create the necessary directories
directories:
	mkdir -p $(OBJ_DIR) $(BIN_DIR)

# Linking the object files to produce the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

# Compiling each source file to an object file
$(OBJ_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove object files and the executable
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Phony targets are targets that do not represent a file
.PHONY: all clean directories
