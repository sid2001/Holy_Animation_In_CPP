CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = animation
SOURCES = main.cpp Shapes/primitives.cpp Shapes/cube.cpp Shapes/plane.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
