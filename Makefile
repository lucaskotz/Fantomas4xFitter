# Compiler and Flags
CXX = g++
CXXFLAGS = -Wall -std=c++17  -g # You can modify flags based on your needs (e.g., debugging, optimization)

# Source and Output
SRC = metacoltest.cc fantomas.cc
OUT = metacoltest.x  # Name of the output executable

# Rules
$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

# Clean up compiled files
clean:
	rm -f $(OUT)
