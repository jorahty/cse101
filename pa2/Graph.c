// James Tennant • jtennant • pa1

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

// ██ Private Types ██

typedef struct GraphObj {
   List* neighbors; // Neighbors of each vertex
   char* color;     // Color of each vertex (w/g/b)
   int* parent;     // Parent of each vertex
   int* distance;   // Each vertice's distance to source
   int order;       // Number of vertices
   int size;        // Number of edges
   int source;      // Most recent source vertex
} GraphObj;

// ██ Constructors & Destructors ██

// Create new Graph with n vertices and no edges
Graph newGraph(int n) {
	n++; // Array length is n + 1
	Graph G = malloc(sizeof(Graph));
	G->neighbors = calloc(n, sizeof(List));
	G->color = calloc(n, sizeof(char));
	G->parent = calloc(n, sizeof(int));
	G->distance = calloc(n, sizeof(int));
	G->order = n;
	G->size = 0;
	G->source = NIL;
	return G;
}

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
