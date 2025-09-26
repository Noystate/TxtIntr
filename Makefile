CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2
TARGET = calculator
SOURCE = calculator.cpp

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

.PHONY: clean
