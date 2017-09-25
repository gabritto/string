CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall
VFLAGS = -std=c++11

main: input.o
	$(CC) $(LFLAGS) $(VFLAGS) input.o main.cpp -o main

input.o: input.cpp input.h
	$(CC) $(CFLAGS) $(VFLAGS) input.cpp