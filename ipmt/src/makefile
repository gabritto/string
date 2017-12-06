OBJS = main.cpp util.o index.o search.o
CC = g++
CFLAGS = -c
LFLAGS = 
VFLAGS = -std=c++11 -O2

all: main clean
	
main: $(OBJS)
	@mkdir -p ../bin/
	$(CC) $(LFLAGS) $(VFLAGS) $(OBJS) -o ../bin/ipmt

util.o: util.cpp util.hpp
	$(CC) $(CFLAGS) $(VFLAGS) util.cpp

index.o: index.cpp index.hpp
	$(CC) $(CFLAGS) $(VFLAGS) index.cpp

search.o: search.cpp search.hpp
	$(CC) $(CFLAGS) $(VFLAGS) search.cpp


clean:
	@rm -f *.o
