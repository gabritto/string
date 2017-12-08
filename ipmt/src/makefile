OBJS = main.cpp util.o index.o search.o suffixarray.o aho.o lz77.o
CC = c++-7
CFLAGS = -c
LFLAGS = 
VFLAGS = -g -std=c++11 -O2

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

suffixarray.o: suffixarray.cpp suffixarray.hpp
	$(CC) $(CFLAGS) $(VFLAGS) suffixarray.cpp

aho.o: aho.cpp aho.hpp
	$(CC) $(CFLAGS) $(VFLAGS) aho.cpp

lz77.o: lz77.cpp lz77.hpp
	$(CC) $(CFLAGS) $(VFLAGS) lz77.cpp


clean:
	@rm -f *.o
