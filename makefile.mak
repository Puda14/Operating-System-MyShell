TinyShell: TinyShell.o process.o dir_file.o
	g++ -o TinyShell TinyShell.o process.o dir_file.o

TinyShell.o: TinyShell.cpp process.h dir_file.h
	g++ -c TinyShell.cpp

process.o: process.cpp process.h
	g++ -c process.cpp

dir_file.o: dir_file.cpp dir_file.h
	g++ -c dir_file.cpp