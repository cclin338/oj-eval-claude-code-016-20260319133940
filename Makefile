CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

all: code

code: main.cpp
	$(CXX) $(CXXFLAGS) -o code main.cpp

clean:
	rm -f code

.PHONY: all clean