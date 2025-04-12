# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -Wextra -pedantic -std=c++17 -O3
GTEST_FLAGS := -pthread -lgtest -lgtest_main
LDFLAGS := 

# Source files
SRC := main.cpp decoder.cpp encoder.cpp
OBJ := $(SRC:.cpp=.o)
EXECUTABLE := ascii85

# Test configuration
TEST_SRC := decoder.cpp encoder.cpp tests.cpp
TEST_OBJ := $(TEST_SRC:.cpp=.o)
TEST_EXEC := test_cpp
PYTEST := python3 tests.py

.PHONY: all clean test

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp decoder.h encoder.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# C++ tests build
$(TEST_EXEC): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GTEST_FLAGS) $(LDFLAGS)

# Test targets
test: $(TEST_EXEC)
	@echo "Running C++ tests..."
	@./$(TEST_EXEC)
	@echo "\nRunning Python tests..."
	@$(PYTEST)

# Clean build artifacts
clean:
	rm -f $(EXECUTABLE) $(TEST_EXEC) *.o
