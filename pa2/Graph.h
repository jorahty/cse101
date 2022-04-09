// James Tennant • jtennant • pa1

#pragma once

#include "List.h"
#include <stdlib.h>

#define INF -1 // Infinity
#define NIL 0 // Undefined vertex label

// ██ Public Types ██

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
