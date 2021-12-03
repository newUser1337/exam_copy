all: main.c rvx.c hash.o
	gcc -g main.c hash.o -o program.out
	gcc -g rvx.c hash.o -o rvx.out
hash.o: hash.c hash.h
	gcc -g -c hash.c -o hash.o
clean:
	rm -f program.out
	rm -f rvx.out
	rm -f *.o