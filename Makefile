CFLAGS=-Wall -g -O2
CC=g++

node.o: clique.o
	$(CC) $(CFLAGS) -c node.cpp

clique.o:
	$(CC) $(CFLAGS) -c clique.cpp

clean:
	rm -rf *.o
