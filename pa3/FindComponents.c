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
    int roots = 0;
    for (moveFront(S); index(S) != -1; moveNext(S)) {
        if (getParent(Gᵀ, get(S)) == NIL) roots++;
    }
    fprintf(out, "\nG contains %d strongly connected components:\n", roots);

    // Determine strong components of G
    int root = 0;
    int walk = 0;
    for (moveBack(S); index(S) != -1; movePrev(S)) { // Walk up S
        walk++;
        int x = get(S);
        if (getParent(Gᵀ, x) == NIL) { // Encounter nil parent
            root++;
            fprintf(out, "Component %d:", root);

            // Print down (and walk back up)
            fprintf(out, " %d", x);
            for (int i = 0; i < walk - 1; i++) {
                moveNext(S);
                fprintf(out, " %d", get(S));
            }
            for (int i = 0; i < walk - 1; i++) {
                movePrev(S);
            }

            fprintf(out, "\n");
            walk = 0;
        }
    }

    // Free S, G, and Gᵀ
    freeList(&S);
    freeGraph(&G);
    freeGraph(&Gᵀ);

    // Close files
    fclose(in);
    fclose(out);

    return 0;
}
