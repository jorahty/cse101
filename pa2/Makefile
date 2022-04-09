# James Tennant • jtennant • pa2

BASE_SOURCES = Graph.c List.c
BASE_OBJECTS = Graph.o List.o
HEADERS      = Graph.h List.h
COMPILE      = gcc -std=c17 -Wall -c
LINK         = gcc -std=c17 -Wall -o

all: FindPath GraphTest

FindPath: FindPath.o $(BASE_OBJECTS)
	$(LINK) FindPath FindPath.o $(BASE_OBJECTS)

GraphTest: GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

FindPath.o: FindPath.c $(HEADERS)
	$(COMPILE) FindPath.c

GraphTest.o: GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

$(BASE_OBJECTS): $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean:
	rm -f FindPath GraphTest *.o

format:
	clang-format -i -style=file *.c *.h
