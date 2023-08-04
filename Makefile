SHELL=/bin/bash

CFLAGS=-std=c11 -Wpedantic -Wall

all :		tsfc.exe

tsfc.exe :	tsfc.o 
		gcc -o tsfc.exe tsfc.o 

tsfc.o :	tsfc.c  
		gcc -c ${CFLAGS} tsfc.c

clean:		
		-rm    tsfc.exe *.o