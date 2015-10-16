all: e1 e2 e3 e4 e5 e6
a.exe: e.cpp Makefile
	g++ -std=c++11 e.cpp -Wall
%: %.in a.exe
	./a < $<
