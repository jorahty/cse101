// James Tennant • jtennant • pa3

#pragma once

#include "List.h"
#include <stdlib.h>

#define INF -1 // Infinity (distance)
#define NIL 0 // Absent/Nonexistent (vertex)
#define UNDEF -1 // Undefined (time)

// ██ Public Types ██

typedef struct GraphObj* Graph;

// ██ Constructors & Destructors ██

Graph newGraph(int n);
void freeGraph(Graph* pG);

// ██ Access Functions ██

int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u); // Pre: 1 ≤ u ≤ n = getOrder(G)
int getDiscover(Graph G, int u); // Pre: 1 ≤ u ≤ n = getOrder(G)
int getFinish(Graph G, int u); // Pre: 1 ≤ u ≤ n = getOrder(G)

// ██ Manipulation Procedures ██

void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void DFS(Graph G, List S); // Pre: length(S) == getOrder(G)

// ██ Other Functions ██

Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);
