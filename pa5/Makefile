# James Tennant • jtennant • pa5

all: Shuffle ListTest

Shuffle: Shuffle.o List.o
	g++ -std=c++17 -Wall -o Shuffle Shuffle.o List.o 

Shuffle.o: List.h Shuffle.cpp
	g++ -std=c++17 -Wall -c Shuffle.cpp

ListTest: ListTest.o List.o
	g++ -std=c++17 -Wall -o ListTest ListTest.o List.o 

ListTest.o: List.h ListTest.cpp
	g++ -std=c++17 -Wall -c ListTest.cpp

List.o: List.h List.cpp
	g++ -std=c++17 -Wall -c List.cpp

clean:
	rm -f Shuffle Shuffle.o ListTest ListTest.o List.o

format:
	clang-format -i -style=file *.cpp *.h
