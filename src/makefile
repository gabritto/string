OBJS = main.cpp input.o util.o ahocorasick.o ukkonen.o boyermoore.o parser.o
CC = g++
CFLAGS = -c
LFLAGS = 
VFLAGS = -std=c++11 -O2 -Wall -Wconversion -Wextra

all: main clean

main: $(OBJS)
	$(CC) $(LFLAGS) $(VFLAGS) $(OBJS) -o main

input.o: input.cpp input.hpp
	$(CC) $(CFLAGS) $(VFLAGS) input.cpp

util.o: util.cpp util.hpp
	$(CC) $(CFLAGS) $(VFLAGS) util.cpp

ahocorasick.o: ahocorasick.cpp ahocorasick.hpp
	$(CC) $(CFLAGS) $(VFLAGS) ahocorasick.cpp

boyermoore.o: boyermoore.cpp boyermoore.hpp
	$(CC) $(CFLAGS) $(VFLAGS) boyermoore.cpp

ukkonen.o: ukkonen.cpp ukkonen.hpp
	$(CC) $(CFLAGS) $(VFLAGS) ukkonen.cpp

parser.o: parser.cpp parser.hpp
	$(CC) $(CFLAGS) $(VFLAGS) parser.cpp
	
clean:
	@rm -f *.o
