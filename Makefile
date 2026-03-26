CXX = clang++
CC = clang

CXXFLAGS = -std=c++17 -Wall -g -Idependencies/include
CFLAGS = -Wall -g -Idependencies/include

LDFLAGS = dependencies/lib/libglfw.3.4.dylib \
          -framework OpenGL \
          -framework Cocoa \
          -framework IOKit \
          -framework CoreVideo \
          -framework CoreFoundation \
          -Wno-deprecated

app: main.o glad.o
	$(CXX) main.o glad.o -o app $(LDFLAGS)

main.o: main.cpp shader_s.h
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

glad.o: glad.c
	$(CC) $(CFLAGS) -c glad.c -o glad.o

run: app
	./app

clean:
	rm -f *.o app

all:
	rm -f *.o app
	$(MAKE)
	./app

.PHONY: clean run all