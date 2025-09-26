CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -O2
TARGET = calculator
SOURCE = calculator.cpp

# Для поддержки русского языка в Linux
RUSSIAN_FLAGS = -DLOCALE_RU

$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(RUSSIAN_FLAGS) -o $(TARGET) $(SOURCE)

clean:
	rm -f $(TARGET)

.PHONY: clean
