OBJS = main.cpp input.o util.o ahocorasick.o
CC = g++
CFLAGS = -Wall -c
LFLAGS = -Wall
VFLAGS = -std=c++11 -O2

main: $(OBJS)
	$(CC) $(LFLAGS) $(VFLAGS) $(OBJS) -o main

input.o: input.cpp input.hpp
	$(CC) $(CFLAGS) $(VFLAGS) input.cpp

util.o: util.cpp util.hpp
	$(CC) $(CFLAGS) $(VFLAGS) util.cpp

ahocorasick.o: ahocorasick.cpp ahocorasick.hpp
	$(CC) $(CFLAGS) $(VFLAGS) ahocorasick.cpp

clean:
	rm -f *.o
	rm -f *.exe
	rm main