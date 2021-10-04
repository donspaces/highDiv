
LargeInt.o: LargeInt.cpp LargeInt.h
	g++ -c LargeInt.cpp -std=c++11
LargeReal.o: LargeReal.cpp LargeReal.h
	g++ -c LargeReal.cpp -std=c++11

main: LargeInt.o
	g++ -o main.o main.cpp LargeInt.o -std=c++11
main2: LargeInt.o LargeReal.o
	g++ -o main2.o main2.cpp LargeInt.o LargeReal.o -std=c++11

clean:
	rm -rf *.o core
	
