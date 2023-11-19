# Compiler settings
CXX = g++
EMXX = em++

# Compiler flags
CXXFLAGS = -g -Wall -Wextra -std=c++17 -Isrc/include
EMFLAGS = -Isrc/include

# Linker flags for WebAssembly
EM_LDFLAGS = -s WASM=1 -s -s WASM=1 -s FULL_ES2=1 -s FULL_ES3=1 -s USE_WEBGL2=1 -s EXIT_RUNTIME=1 -s ERROR_ON_UNDEFINED_SYMBOLS=1 -s EXTRA_EXPORTED_RUNTIME_METHODS=["UTF16ToString","stringToUTF16"] --bind -s FETCH=1 -O2 -s ALLOW_MEMORY_GROWTH=1 -s ERROR_ON_UNDEFINED_SYMBOLS=0

# Source directories
SRC_DIRS = src src/circuit src/load src/load/components src/sources src/sources/AC src/sources/DC src/simulator
WASM_SRC_DIR = wasm/src wasm/src/circuit wasm/src/load wasm/src/load/components wasm/src/sources wasm/src/sources/AC wasm/src/sources/DC wasm/src/simulator

# Object and binary directories
OBJ_DIR = obj
WASM_OBJ_DIR = wasm/obj
BIN_DIR = bin
WASM_BIN_DIR = wasm/bin

# Source files and object files
SOURCES = $(shell find $(SRC_DIRS) -name *.cpp)
WASM_SOURCES = $(shell find $(WASM_SRC_DIR) -name *.cpp)
OBJECTS = $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)
WASM_OBJECTS = $(WASM_SOURCES:%.cpp=$(WASM_OBJ_DIR)/%.o)

# Executable names
EXECUTABLE = $(BIN_DIR)/circuit_simulator
WASM_EXECUTABLE = $(WASM_BIN_DIR)/project_interface.js

# Default target
all: directories $(EXECUTABLE) wasm

# Create necessary directories
directories:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR) $(WASM_OBJ_DIR) $(WASM_BIN_DIR)

# Compile C++ source files to object files
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile WebAssembly source files to object files
$(WASM_OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(EMXX) $(EMFLAGS) -c $< -o $@

# Link object files to create the C++ executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $^ -o $@

# Link WebAssembly object files to create the WebAssembly module
wasm: $(WASM_OBJECTS)
	$(EMXX) $(EM_LDFLAGS) $^ -o $(WASM_EXECUTABLE)

# Clean up generated files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(WASM_OBJ_DIR) $(WASM_BIN_DIR)

# Phony targets
.PHONY: all clean directories wasm
