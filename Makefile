# idocohen963@gmail.com

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -g

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
	valgrind --leak-check=full --show-leak-kinds=all ./$(TEST_EXE)

# Clean up
clean:
	rm -rf $(BUILD_DIR) $(MAIN_EXE) $(TEST_EXE)

# מילון דגלים, קיצורים ומשתנים אוטומטיים:
# -p                  : ב-mkdir - יוצר גם תיקיות אב חסרות (parents)
# -rf                 : ב-rm - מסיר קבצים/תיקיות רקורסיבית וללא בקשת אישור (recursive, force)
# -std=c++11          : לקמפלר - השתמש בתקן C++11
# -Wall               : לקמפלר - הצג את כל האזהרות
# -Wextra             : לקמפלר - הצג אזהרות נוספות
# -pedantic           : לקמפלר - הקפדה על תקן C++
# -g                  : לקמפלר - הוסף מידע דיבאג
# --leak-check=full   : ל-valgrind - בדיקה מלאה של דליפות זיכרון
# --show-leak-kinds=all : ל-valgrind - הצג את כל סוגי הדליפות
# $@                  :משתנה אוטומטי במייקפייל שמייצג את שם המטרה (target) הנוכחית.
# $^                  : משתנה אוטומטי במייקפייל שמייצג את כל התלויות (dependencies) של המטרה הנוכחית, מופרדות ברווחים.
