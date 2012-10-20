CFLAGS=-Wall -g -O2
CC=g++

vertex_cover: vertex_cover.o search.o node.o clique.o
	$(CC) $(CFLAGS) -o vertex_cover clique.o node.o search.o vertex_cover.o

vertex_cover.o: search.o node.o clique.o
	$(CC) $(CFLAGS) -c vertex_cover.cpp

search.o: node.o clique.o
	$(CC) $(CFLAGS) -c search.cpp

node.o: clique.o
	$(CC) $(CFLAGS) -c node.cpp

clique.o:
	$(CC) $(CFLAGS) -c clique.cpp

clean:
	rm -rf *.o
