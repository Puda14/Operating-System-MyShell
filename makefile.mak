TinyShell: TinyShell.o process.o
	g++ -o TinyShell TinyShell.o process.o

TinyShell.o: TinyShell.cpp process.h
	g++ -c TinyShell.cpp

process.o: process.cpp process.h
	g++ -c process.cpp