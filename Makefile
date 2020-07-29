HugeInt : main.o hugeint.o
	g++ -o HugeInt hugeint.o main.o

hugeint.o : hugeint.cpp hugeint.h
	g++ -c hugeint.cpp

main.o : main.cpp hugeint.h
	g++ -c main.cpp

clean :
	rm HugeInt *.o
