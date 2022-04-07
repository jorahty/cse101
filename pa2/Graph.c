// James Tennant • jtennant • pa1

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

// ██ Private Types ██

typedef struct GraphObj* Graph;

// ██ Constructors & Destructors ██

Graph newGraph(int n);
void freeGraph(Graph* pG);

// ██ Access Functions ██

int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

// ██ Manipulation Procedures ██

void makeNull(Graph G);
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);

// ██ Other Functions ██

void printGraph(FILE* out, Graph G);
