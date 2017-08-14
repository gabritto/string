CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall
VFLAGS = -std=c++11

main: z.o
	$(CC) $(LFLAGS) $(VFLAGS) z.o main.cpp -o main

z.o: z.cpp z.hpp
	$(CC) $(CFLAGS) $(VFLAGS) z.cpp
