all: wHeap.o wHeapUtil.o sHeap.o sHeapUtil.o wHash.o wHashUtil.o sHash.o sHashUtil.o
	gcc -o wHeap wHeap.o wHeapUtil.o 
	gcc -o sHeap sHeap.o sHeapUtil.o
	gcc -o wHash wHash.o wHashUtil.o
	gcc -o sHash sHash.o sHashUtil.o

wHeap.o: wHeap.c wHeap.h
	gcc -Wall -pedantic -ansi -c -std=c99 wHeap.c -g

wHeapUtil.o: wHeapUtil.c wHeapUtil.h
	gcc -Wall -pedantic -ansi -c -std=c99 wHeapUtil.c -g

sHeap.o: sHeap.c sHeap.h
	gcc -Wall -pedantic -ansi -c -std=c99 sHeap.c -g

sHeapUtil.o: sHeapUtil.c sHeapUtil.h
	gcc -Wall -pedantic -ansi -c -std=c99 sHeapUtil.c -g

wHash.o: wHash.c wHash.h
	gcc -Wall -pedantic -ansi -c -std=c99 wHash.c -g

wHashUtil.o: wHashUtil.c wHashUtil.h
	gcc -Wall -pedantic -ansi -c -std=c99 wHashUtil.c -g

sHash.o: sHash.c sHash.h
	gcc -Wall -pedantic -ansi -c -std=c99 sHash.c -g

sHashUtil.o: sHashUtil.c sHashUtil.h
	gcc -Wall -pedantic -ansi -c -std=c99 sHashUtil.c -g
