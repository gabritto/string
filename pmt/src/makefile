OBJS = main.cpp input.o util.o ahocorasick.o ukkonen.o boyermoore.o parser.o \
bruteforce.o z.o sellers.o shiftor.o wumanber.o
CC = g++
CFLAGS = -c
LFLAGS = 
VFLAGS = -std=c++11 -O2

all: main clean
	
main: $(OBJS)
	@mkdir -p ../bin/
	$(CC) $(LFLAGS) $(VFLAGS) $(OBJS) -o ../bin/pmt

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

bruteforce.o: bruteforce.cpp bruteforce.hpp
	$(CC) $(CFLAGS) $(VFLAGS) bruteforce.cpp

z.o: z.cpp z.hpp
	$(CC) $(CFLAGS) $(VFLAGS) z.cpp

sellers.o: sellers.cpp sellers.hpp
	$(CC) $(CFLAGS) $(VFLAGS) sellers.cpp

shiftor.o: shiftor.cpp shiftor.hpp
	$(CC) $(CFLAGS) $(VFLAGS) shiftor.cpp

wumanber.o: wumanber.cpp wumanber.hpp
	$(CC) $(CFLAGS) $(VFLAGS) wumanber.cpp

clean:
	@rm -f *.o
