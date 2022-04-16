// James Tennant • jtennant • pa3

#include "Graph.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    // Check for correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        return 1;
    }

    // Open input file for reading
    FILE* in = fopen(argv[1], "r");
    if (in == NULL) {
        printf("Unable to open file %s for reading\n", argv[1]);
        return 1;
    }

    // Open output file for writing
    FILE* out = fopen(argv[2], "w");
    if (out == NULL) {
        printf("Unable to open file %s for writing\n", argv[2]);
        return 1;
    }

    // Create Graph
    int n;
    fscanf(in, "%d\n", &n); // Get number of vertices n
    Graph G = newGraph(n);
    int u, v;
    while (fscanf(in, "%d %d\n", &u, &v) != EOF) {
        if (u == 0 && v == 0) break;
        addArc(G, u, v); // Add arcs
    }

    // Print Graph
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);

    // Generate S
    List S = newList();
    for (int i = 1; i <= getOrder(G); i++) {
        append(S, i);
    }

    DFS(G, S);

    Graph Gᵀ = transpose(G);

    DFS(Gᵀ, S); // Now S can be used to print components

    // Count components
    // by counting nil-parent vertices (roots)
    int roots = 0;
    for (moveFront(S); index(S) != -1; moveNext(S)) {
        int x = get(S);
        if (getParent(Gᵀ, x) == NIL) roots++;
    }

    // Allocate memory for array of components
    List* components = calloc(roots, sizeof(List));
    for (int i = 0; i < roots; i++) {
        components[i] = newList();
    }

    int i = 0;
    for (moveBack(S); index(S) != -1; movePrev(S)) {
        int x = get(S);

        prepend(components[i], x);

        if (getParent(Gᵀ, x) == NIL) i++;
    }

    // Print components
    fprintf(out, "\nG contains %d strongly connected components:\n", roots);
    for (int i = 0; i < roots; i++) {
        fprintf(out, "Component %d: ", i + 1);
        printList(out, components[i]);
        fprintf(out, "\n");
    }

    // Free array of components
    for (int i = 0; i < roots; i++) {
        List L = components[i];
        freeList(&L);
    }
    free(components);

    // Free S, G, and Gᵀ
    freeList(&S);
    freeGraph(&G);
    freeGraph(&Gᵀ);

    // Close files
    fclose(in);
    fclose(out);

    return 0;
}
