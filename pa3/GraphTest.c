// James Tennant • jtennant • pa3

#include "Graph.h"
#include "List.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Declare helper functions
void runGraphClient(void);
void printGraphInfo(Graph G);

int main(void) {

    // Run the tests from GraphClient.c
    runGraphClient();

    // Change output color
    printf("\033[0;32m");

    // Lecture example 1
    printf("Lecture example 1:\n");
    Graph G = newGraph(6);
    addEdge(G, 1, 2);
    addEdge(G, 1, 3);
    addEdge(G, 2, 4);
    addEdge(G, 2, 5);
    addEdge(G, 2, 6);
    addEdge(G, 3, 4);
    addEdge(G, 4, 5);
    addEdge(G, 5, 6);
    printGraph(stdout, G);
    List S = newList();
    for (int u = 1; u <= getOrder(G); u++) {
        append(S, u);
    }
    DFS(G, S);
    printGraphInfo(G);
    freeList(&S);
    freeGraph(&G);

    // Lecture Example 2
    printf("\n\nLecture example 2:\n");
    G = newGraph(7);
    addEdge(G, 1, 2);
    addEdge(G, 1, 4);
    addEdge(G, 2, 4);
    addEdge(G, 2, 5);
    addEdge(G, 3, 6);
    addEdge(G, 3, 7);
    addEdge(G, 6, 7);
    printGraph(stdout, G);
    S = newList();
    for (int u = 1; u <= getOrder(G); u++) {
        append(S, u);
    }
    DFS(G, S);
    printGraphInfo(G);
    freeList(&S);
    freeGraph(&G);

    // Lecture example 3
    printf("\n\nLecture example 3:\n");
    G = newGraph(8);
    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 2, 5);
    addArc(G, 2, 6);
    addArc(G, 3, 4);
    addArc(G, 3, 7);
    addArc(G, 4, 3);
    addArc(G, 4, 8);
    addArc(G, 5, 1);
    addArc(G, 5, 6);
    addArc(G, 6, 7);
    addArc(G, 7, 6);
    addArc(G, 7, 8);
    addArc(G, 8, 8);
    printGraph(stdout, G);
    S = newList();
    for (int u = 1; u <= getOrder(G); u++) {
        append(S, u);
    }
    DFS(G, S);
    printf("\n");
    printList(stdout, S);
    printf("\n\n");
    Graph T = transpose(G);
    printGraph(stdout, T);
    printf("\n");
    DFS(T, S);
    printList(stdout, S);
    printf("\n");
    printGraphInfo(T);
    printf("\n");
    freeGraph(&T);
    freeList(&S);
    freeGraph(&G);

    // Reset output color
    printf("\033[0m");

    return 0;
}

void printGraphInfo(Graph G) {
    printf("\nx: d  f  p");
    for (int u = 1; u <= getOrder(G); u++) {
        int d = getDiscover(G, u);
        int f = getFinish(G, u);
        int p = getParent(G, u);
        printf("\n%d: %-2d %-2d %d", u, d, f, p);
    }
}

void runGraphClient(void) {
    printf("Test from GraphClient.c:\n");
    int i, n = 8;
    List S = newList();
    Graph G = newGraph(n);
    Graph T = NULL, C = NULL;
    for (i = 1; i <= n; i++) {
        append(S, i);
    }
    addArc(G, 1, 2);
    addArc(G, 1, 5);
    addArc(G, 2, 5);
    addArc(G, 2, 6);
    addArc(G, 3, 2);
    addArc(G, 3, 4);
    addArc(G, 3, 6);
    addArc(G, 3, 7);
    addArc(G, 3, 8);
    addArc(G, 6, 5);
    addArc(G, 6, 7);
    addArc(G, 8, 4);
    addArc(G, 8, 7);
    printGraph(stdout, G);
    DFS(G, S);
    fprintf(stdout, "\n");
    fprintf(stdout, "x:  d  f  p\n");
    for (i = 1; i <= n; i++) {
        printf("%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
    }
    fprintf(stdout, "\n");
    printList(stdout, S);
    fprintf(stdout, "\n");
    T = transpose(G);
    C = copyGraph(G);
    fprintf(stdout, "\n");
    printGraph(stdout, C);
    fprintf(stdout, "\n");
    printGraph(stdout, T);
    fprintf(stdout, "\n");
    DFS(T, S);
    fprintf(stdout, "\n");
    fprintf(stdout, "x:  d  f  p\n");
    for (i = 1; i <= n; i++) {
        printf("%d: %2d %2d %2d\n", i, getDiscover(T, i), getFinish(T, i), getParent(T, i));
    }
    fprintf(stdout, "\n");
    printList(stdout, S);
    fprintf(stdout, "\n");
    freeList(&S);
    freeGraph(&G);
    freeGraph(&T);
    freeGraph(&C);
}