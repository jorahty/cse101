# James Tennant • jtennant • pa1

BASE_SOURCES = Graph.c List.c
BASE_OBJECTS = Graph.o List.o
HEADERS      = Graph.h List.h
COMPILE      = gcc -std=c17 -Wall -c
LINK         = gcc -std=c17 -Wall -o

all: FindPath GraphClient

FindPath: FindPath.o $(BASE_OBJECTS)
	$(LINK) FindPath FindPath.o $(BASE_OBJECTS)

GraphClient: GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

FindPath.o: FindPath.c $(HEADERS)
	$(COMPILE) FindPath.c

GraphClient.o: GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

$(BASE_OBJECTS): $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

clean:
	rm -f FindPath GraphClient *.o
