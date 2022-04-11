// James Tennant • jtennant • pa2

#include "Graph.h"
#include "List.h"
#include <stdio.h>

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
        addEdge(G, u, v); // Add edges
    }
    printGraph(out, G); // Print adjacency list representaion

    // Run BFS
    int s, d;
    while (fscanf(in, "%d %d\n", &s, &d) != EOF) {
        if (s == 0 && d == 0) break;
        BFS(G, s);

        // Print distance
        fprintf(out, "\nThe distance from %d to %d is %d\n", s, d, getDist(G, d));

        // Print path
        List path = newList();
        getPath(path, G, d);
        fprintf(out, "A shortest %d-%d path is: ", s, d);
        printList(out, path);
        fprintf(out, "\n");
    }

    // Free the Graph
    freeGraph(&G);

    // Close files
    fclose(in);
    fclose(out);

    return 0;
}
