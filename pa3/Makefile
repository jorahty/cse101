# James Tennant • jtennant • pa3

BASE_SOURCES = Graph.c List.c
BASE_OBJECTS = Graph.o List.o
HEADERS      = Graph.h List.h
COMPILE      = gcc -std=c17 -Wall -c
LINK         = gcc -std=c17 -Wall -o

all: FindComponents GraphTest

FindComponents: FindComponents.o $(BASE_OBJECTS)
	$(LINK) FindComponents FindComponents.o $(BASE_OBJECTS)

GraphTest: GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

FindComponents.o: FindComponents.c $(HEADERS)
	$(COMPILE) FindComponents.c

GraphTest.o: GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

$(BASE_OBJECTS): $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean:
	rm -f FindComponents GraphTest *.o

format:
	clang-format -i -style=file *.c *.h
