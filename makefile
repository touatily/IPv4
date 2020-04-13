main : main.o ipv4.h ipv4.o main.cpp ipv4.cpp
	g++ -o main main.o source.o

ipv4.o : ipv4.h ipv4.cpp
	g++ -c ipv4.cpp

main.o : ipv4.h main.cpp
	g++ -c main.cpp

lib : ipv4.h ipv4.cpp ipv4.o
	ar rcs libipv4.a ipv4.o

clean :
	rm -f main.o ipv4.o main libipv4.a
