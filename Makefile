CC=g++
CFLAGS=-g -Wall -pedantic -ansi -c -I/usr/local/include
LDFLAGS=-g -L/usr/local/lib
LIBS=-lGLEW -lglfw3
FRAMEWORKS= -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=main

all: $(SOURCES) $(EXECUTABLE)

run: all
	./$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(LIBS) $(OBJECTS) $(FRAMEWORKS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE)

#~/d/opengl ❯❯❯ cc -g -O0 main.cpp -o main -I/usr/local/include -L/usr/local/lib -lGLEW -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo && ./main
