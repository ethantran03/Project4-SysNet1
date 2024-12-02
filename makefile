# Compiler settings
CXX = g++
CXXFLAGS = -O0 -std=c++17 -Wall -Wextra

# Output executable
TARGET = matrix

# Source files
SRC = matrix.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Rule to build the target
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Rule to generate object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(TARGET) $(OBJ)

# Phony targets
.PHONY: clean
