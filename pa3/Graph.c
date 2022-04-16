// James Tennant • jtennant • pa3

#include "Graph.h"
#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// ██ Private Types ██

typedef struct GraphObj {
    List* neighbors; // Neighbors of each vertex
    char* color; // Color of each vertex (w/g/b)
    int* parent; // Parent of each vertex
    int* discover; // Discover time of each vertex
    int* finish; // Finish time of each vertex
    int order; // Number of vertices
    int size; // Number of edges
} GraphObj;

// ██ Constructors & Destructors ██

// Create new Graph with n vertices and no edges
Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));

    int length = n + 1; // Array length is n + 1
    G->neighbors = calloc(length, sizeof(List));
    G->color = calloc(length, sizeof(char));
    G->parent = calloc(length, sizeof(int));
    G->discover = calloc(length, sizeof(int));
    G->finish = calloc(length, sizeof(int));

    // Initialize vertex properties
    for (int u = 1; u <= n; u++) {
        G->neighbors[u] = newList();
        G->color[u] = 'w';
        G->parent[u] = NIL;
        G->discover[u] = NIL;
        G->finish[u] = NIL;
    }

    G->order = n;
    G->size = 0;
    return G;
}

// Free all memory & set *pG to NULL
void freeGraph(Graph* pG) {
    if (pG && *pG) {
        if ((*pG)->neighbors) {
            for (int u = 1; u <= (*pG)->order; u++) {
                freeList(&((*pG)->neighbors[u]));
            }
            free((*pG)->neighbors);
        }
        if ((*pG)->color) free((*pG)->color);
        if ((*pG)->parent) free((*pG)->parent);
        if ((*pG)->discover) free((*pG)->discover);
        if ((*pG)->finish) free((*pG)->finish);
        free(*pG);
        *pG = NULL;
    }
}

// ██ Access Functions ██

// Return order
int getOrder(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getOrder() on NULL Graph reference\n");
        exit(1);
    }
    return G->order;
}

// Return size
int getSize(Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getSize() on NULL Graph reference\n");
        exit(1);
    }
    return G->size;
}

// Return parent of vertex u
// Pre: 1 ≤ u ≤ getOrder()
int getParent(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getParent() on NULL Graph reference\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getParent() with vertex out of range\n");
        exit(1);
    }
    return G->parent[u];
}

// Return discover time of vertex u
// Pre: 1 ≤ u ≤ getOrder()
int getDiscover(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getDiscover() on NULL Graph reference\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getDiscover() with vertex out of range\n");
        exit(1);
    }
    return G->discover[u];
}

// Return finish time of vertex u
// Pre: 1 ≤ u ≤ getOrder()
int getFinish(Graph G, int u) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling getFinish() on NULL Graph reference\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling getFinish() with vertex out of range\n");
        exit(1);
    }
    return G->finish[u];
}

// ██ Manipulation Procedures ██

// Add new edge joining u and v
// u is added to adjacency List of v
// v is added to adjacency List of u
// Maintain Lists in order of increasing vertex label
// Pre: 1 ≤ u ≤ getOrder()
void addEdge(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling addEdge() with vertex out of range\n");
        exit(1);
    }

    // 1. Add u to adjacency list of v
    bool edgeWasAdded = false;
    List L = G->neighbors[v];
    for (moveFront(L); 1; moveNext(L)) { // Scan for a place to insert i

        // Have we reached the end of the List?
        if (index(L) == -1) {
            append(L, u);
            edgeWasAdded = true;
            break;
        }

        // Does u belong before the cursor element?
        if (u < get(L)) {
            insertBefore(L, u);
            edgeWasAdded = true;
            break;
        }

        // Does u equal the cursor element?
        if (u == get(L)) break;
    }

    // 2. Add v to adjacency list of u
    L = G->neighbors[u];
    for (moveFront(L); 1; moveNext(L)) { // Scan for a place to insert i

        // Have we reached the end of the List?
        if (index(L) == -1) {
            append(L, v);
            edgeWasAdded = true;
            break;
        }

        // Does v belong before the cursor element?
        if (v < get(L)) {
            insertBefore(L, v);
            edgeWasAdded = true;
            break;
        }

        // Does v equal the cursor element?
        if (v == get(L)) break;
    }

    if (edgeWasAdded) G->size++;
}

// Pre: 1 ≤ u ≤ getOrder()
void addArc(Graph G, int u, int v) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling addArc() on NULL Graph reference\n");
        exit(1);
    }
    if (u < 1 || u > getOrder(G) || v < 1 || v > getOrder(G)) {
        fprintf(stderr, "Graph Error: calling addArc() with vertex out of range\n");
        exit(1);
    }

    // Add v to adjacency list of u
    List L = G->neighbors[u];
    for (moveFront(L); 1; moveNext(L)) { // Scan for a place to insert i

        // Have we reached the end of the List?
        if (index(L) == -1) {
            append(L, v);
            G->size++;
            return;
        }

        // Does v belong before the cursor element?
        if (v < get(L)) {
            insertBefore(L, v);
            G->size++;
            return;
        }

        // Does v equal the cursor element?
        if (v == get(L)) return;
    }
}

int time = 0;
void Visit(Graph G, List S, int x);

// Pre: length(S) == getOrder(G)
void DFS(Graph G, List S) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling DFS() on NULL Graph reference\n");
        exit(1);
    }
    if (length(S) != getOrder(G)) {
        fprintf(stderr, "Graph Error: calling DFS() with List of invalid length\n");
        exit(1);
    }

    // Initialize
    for (int u = 1; u <= getOrder(G); u++) {
        G->color[u] = 'w';
        G->parent[u] = NIL;
        G->discover[u] = NIL;
        G->finish[u] = NIL;
    }

    time = 0;

    List L = copyList(S); // Let L be loop order (given by S)
    clear(S); // Now prepare S to be stack of vertices by finish time

    // Main loop of DFS
    for (moveFront(L); index(L) != -1; moveNext(L)) {
        int x = get(L);
        if (G->color[x] == 'w') Visit(G, S, x);
    }

    freeList(&L);
}

void Visit(Graph G, List S, int x) {
    G->discover[x] = (++time); // Discover x
    G->color[x] = 'g';
    List N = G->neighbors[x];
    for (moveFront(N); index(N) != -1; moveNext(N)) { // For every neighbor
        int y = get(N);
        if (G->color[y] == 'w') {
            G->parent[y] = x;
            Visit(G, S, y);
        }
    }
    G->color[x] = 'b';
    G->finish[x] = (++time); // Finish x
    prepend(S, x);
}

// ██ Other Functions ██

Graph transpose(Graph G) {
    Graph T = newGraph(getOrder(G)); // new null graph with same # of vertices

    // add arcs
    for (int x = 1; x <= getOrder(G); x++) { // for every list
        List L = G->neighbors[x];
        for (moveFront(L); index(L) != -1; moveNext(L)) { // for every vertex in list
            int y = get(L);
            addArc(T, y, x); // add arc from y to x
        }
    }

    return T;
}

Graph copyGraph(Graph G) {
    Graph C = newGraph(getOrder(G));

    for (int u = 1; u <= getOrder(G); u++) {
        List L = C->neighbors[u];
        freeList(&L);
        C->neighbors[u] = copyList(G->neighbors[u]);
    }

    return C;
}

// Print adjacency List representation
void printGraph(FILE* out, Graph G) {
    if (G == NULL) {
        fprintf(stderr, "Graph Error: calling printGraph() on NULL Graph reference\n");
        exit(1);
    }
    for (int u = 1; u <= getOrder(G); u++) {
        fprintf(out, "%d: ", u);
        printList(out, G->neighbors[u]);
        fprintf(out, "\n");
    }
}
