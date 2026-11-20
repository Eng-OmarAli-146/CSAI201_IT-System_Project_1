CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
SOURCES  = $(wildcard *.cpp)
TARGET   = it_system

$(TARGET): $(SOURCES) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) *.o

.PHONY: run clean
