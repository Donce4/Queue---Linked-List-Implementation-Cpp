all: demo test

queue.o: queue.cpp queue.h
	g++ -std=c++11 -c queue.cpp -o queue.o

demo: demo.cpp queue.o
	g++ -std=c++11 demo.cpp queue.o -o demo

test: test.cpp queue.o
	g++ -std=c++11 test.cpp queue.o -o test