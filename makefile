main : main.o source.h source.o main.cpp source.cpp
	g++ -o main main.o source.o

source.o : source.h source.cpp
	g++ -c source.cpp

main.o : source.h main.cpp
	g++ -c main.cpp

lib : source.h source.cpp source.o
	ar rcs libipv4.a source.o

clean :
	rm -f main.o source.o main libipv4.a
