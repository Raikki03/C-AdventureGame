CXX = g++

CXXFLAGS = -O0 -g3 -std=c++17
INCLUDES = -I.

EXECUTABLE = main

SOURCES = main.cpp Room.cpp Object.cpp Enemy.cpp Player.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJECTS) -o $(EXECUTABLE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)
