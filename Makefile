#https://www.softwaretestinghelp.com/cpp-makefile-tutorial/
CC = g++
CFLAGS = -Wall -g -pthread -fopenmp
 
main: main.o Image.o
	$(CC) $(CFLAGS) -o main main.o Image.o
 
main.o: main.cpp Image.hpp
	$(CC) $(CFLAGS) -c main.cpp
 
Image.o: Image.hpp

clean:
	$(RM) main Image.o main.o
