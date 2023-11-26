test: test.o process.o
	g++ -o test test.o process.o

test.o: test.cpp process.h
	g++ -c test.cpp

process.o: process.cpp process.h
	g++ -c process.cpp