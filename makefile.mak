MyShell: MyShell.o process.o
	g++ -o MyShell.o process.o

MyShell.o: MyShell.c process.h
	g++ -c MyShell.c

process.o: process.c process.h
	g++ -c process.c