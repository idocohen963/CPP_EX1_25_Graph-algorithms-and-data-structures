# idocohen963@gmail.com

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic

# Directories
SRC_DIR = src
INCLUDE_DIR = include
TEST_DIR = tests
BUILD_DIR = build

# Source files
SOURCES = $(SRC_DIR)/Graph.cpp $(SRC_DIR)/Queue.cpp $(SRC_DIR)/PriorityQueue.cpp $(SRC_DIR)/UnionFind.cpp $(SRC_DIR)/Algorithms.cpp
MAIN_SRC = $(SRC_DIR)/main.cpp
TEST_SRC = $(TEST_DIR)/test.cpp

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
MAIN_OBJ = $(BUILD_DIR)/main.o
TEST_OBJ = $(BUILD_DIR)/test.o

# Executables
MAIN_EXE = main
TEST_EXE = test

# Targets
.PHONY: all Main test valgrind clean

all: Main test

# Create build directory if it doesn't exist
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile test file
$(TEST_OBJ): $(TEST_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Compile main file
$(MAIN_OBJ): $(MAIN_SRC) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Link main executable
Main: $(OBJECTS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $(MAIN_EXE)

# Link test executable
test: $(OBJECTS) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $(TEST_EXE)
	./$(TEST_EXE)

# Run valgrind on main executable
valgrind: Main
	valgrind --leak-check=full --show-leak-kinds=all ./$(MAIN_EXE)

# Clean up
clean:
	rm -rf $(BUILD_DIR) $(MAIN_EXE) $(TEST_EXE)
