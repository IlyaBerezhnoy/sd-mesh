# Makefile for SD-Mesh project

sd-mesh: main.o util.o
	gcc main.o util.o -o sd-mesh

main.o: main.c
	gcc -c main.c

util.o: lib/util.c
	gcc -c lib/util.c

clean:
	rm -f *.o sd-mesh
