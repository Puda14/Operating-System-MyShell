TinyShell: TinyShell.o process.o dir_file.o env.o
	g++ -o TinyShell TinyShell.o process.o dir_file.o env.o

TinyShell.o: TinyShell.cpp process.h dir_file.h env.h
	g++ -c TinyShell.cpp

dir_file.o: dir_file.cpp dir_file.h process.h
	g++ -c dir_file.cpp

process.o: process.cpp process.h
	g++ -c process.cpp

env.o: env.cpp env.h
	g++ -c env.cpp