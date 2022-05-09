# James Tennant • jtennant • pa6

CC = g++ -std=c++17 -Wall

all: Arithmetic BigIntegerTest ListTest

Arithmetic: Arithmetic.o BigInteger.o List.o
	$(CC) -o Arithmetic Arithmetic.o BigInteger.o List.o

BigIntegerTest: BigIntegerTest.o BigInteger.o List.o
	$(CC) -o BigIntegerTest BigIntegerTest.o BigInteger.o List.o

ListTest: ListTest.o List.o
	$(CC) -o ListTest ListTest.o List.o

#

Arithmetic.o: Arithmetic.cpp BigInteger.h List.h
	$(CC) -c Arithmetic.cpp

BigIntegerTest.o: BigIntegerTest.cpp BigInteger.h List.h
	$(CC) -c BigIntegerTest.cpp

ListTest.o: ListTest.cpp List.h
	$(CC) -c ListTest.cpp

BigInteger.o: BigInteger.cpp BigInteger.h
	$(CC) -c BigInteger.cpp

List.o: List.cpp List.h
	$(CC) -c List.cpp

#

clean:
	rm -rf Arithmetic BigIntegerTest ListTest *.o

format:
	clang-format -i -style=file *.cpp