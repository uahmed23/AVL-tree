CFLAGS = -Wall -std=c99 -pedantic

all: avltree

avltree: avltree.c a4.h avltreeFunctions.o
	gcc $(CFLAGS) -include a4.h -c avltree.c
	gcc $(CFLAGS) avltreeFunctions.o avltree.o -o avltree

avltreeFunctions.o: avltreeFunctions.c a4.h
	gcc $(CFLAGS) -include a4.h -c avltreeFunctions.c -o avltreeFunctions.o


clean:rm -i *.o
