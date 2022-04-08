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
   int* distance;   // Distance to source from each vertex
   int order;       // Number of vertices
   int size;        // Number of edges
   int source;      // Most recent source vertex
} GraphObj;

// ██ Constructors & Destructors ██

// Create new Graph with n vertices and no edges
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));

	int length = n + 1; // Array length is n + 1
	G->neighbors = calloc(length, sizeof(List));
	G->color = calloc(length, sizeof(char));
	G->parent = calloc(length, sizeof(int));
	G->distance = calloc(length, sizeof(int));

	// Initialize vertex properties
	for (int i = 1; i <= length; i++) {
		G->neighbors[i] = newList();
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}
	
	G->order = n;
	G->size = 0;
	G->source = NIL;
	return G;
}

// Free all memory & set *pG to NULL
void freeGraph(Graph* pG) {
	if (pG && *pG) {
		if ((*pG)->neighbors) {
			free((*pG)->neighbors);
		}
		if ((*pG)->color) {
			free((*pG)->color);
		}
		if ((*pG)->parent) {
			free((*pG)->parent);
		}
		if ((*pG)->distance) {
			free((*pG)->distance);
		}
		free(*pG);
		*pG = NULL;
	}
}

// ██ Access Functions ██

// Return order
int getOrder(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getOrder() on NULL Graph reference\n");
		exit(1);
	}
	return G->order;
}

// Return size
int getSize(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getSize() on NULL Graph reference\n");
		exit(1);
	}
	return G->size;
}

// Return (most recent) source
int getSource(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getSource() on NULL Graph reference\n");
		exit(1);
	}
	return G->source;
}

// Return parent of vertex u
// Pre: 1 ≤ u ≤ getOrder()
int getParent(Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getParent() on NULL Graph reference\n");
		exit(1);
	}
	if (u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getParent() with vertex out of range\n");
		exit(1);
	}
	return G->parent[u];
}

// Return distance from source to vertex u
// Pre: 1 ≤ u ≤ getOrder()
int getDist(Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getDist() on NULL Graph reference\n");
		exit(1);
	}
	if (u < 1 || u > getOrder(G)) {
		printf("Graph Error: calling getDist() with vertex out of range\n");
		exit(1);
	}
	return G->distance[u];
}

//	Append vertices of shortest path from source to u
// Append NIL if no such path exists
// See PrintPath in /Examples/Pseudo-Code
// Pre: 1 ≤ u ≤ getOrder(), getSource() != NIL
void getPath(List L, Graph G, int u);

// ██ Manipulation Procedures ██

// Deletes all edges in G,
// restoring it to its original state
void makeNull(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling makeNull() on NULL Graph reference\n");
		exit(1);
	}

	int length = G->order + 1;
	for (int i = 1; i <= length; i++) {
		clear(G->neighbors[i]);
		G->color[i] = 'w';
		G->parent[i] = NIL;
		G->distance[i] = INF;
	}

	G->size = 0;
	G->source = NIL;
}

// Pre: 1 ≤ u ≤ getOrder()
void addEdge(Graph G, int u, int v);

// Pre: 1 ≤ u ≤ getOrder()
void addArc(Graph G, int u, int v);

void BFS(Graph G, int s);

// ██ Other Functions ██

// Print adjacency list representation
void printGraph(FILE* out, Graph G) {
	
}
