// James Tennant • jtennant • pa4

#include "Matrix.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void MatrixClient();

int main(void) {

    printf("\033[0;32m\n"); // Change output color to green
    printf("Hello Matrix!\n\n");

    printf("Matrix I:\n");
    Matrix I = newMatrix(2);
    changeEntry(I, 1, 1, 1);
    changeEntry(I, 1, 2, 2);
    changeEntry(I, 2, 1, 3);
    changeEntry(I, 2, 2, 4);
    printMatrix(stdout, I);
    printf("\n");

    printf("Matrix J:\n");
    Matrix J = newMatrix(2);
    changeEntry(J, 1, 1, 5);
    changeEntry(J, 1, 2, 6);
    changeEntry(J, 2, 1, 7);
    changeEntry(J, 2, 2, 8);
    printMatrix(stdout, J);
    printf("\n");

    printf("I × J:\n");
    Matrix X = product(I, J);
    printMatrix(stdout, X);
    printf("\n");

    printf("I + J:\n");
    Matrix Y = sum(I, J);
    printMatrix(stdout, Y);
    printf("\n");

    printf("I - J:\n");
    Matrix Z = diff(I, J);
    printMatrix(stdout, Z);
    printf("\n");

    freeMatrix(&I);
    freeMatrix(&J);
    freeMatrix(&X);
    freeMatrix(&Y);
    freeMatrix(&Z);

    printf("More testing:\n");

    Matrix M = newMatrix(3);

    printMatrix(stdout, M);

    changeEntry(M, 1, 1, 1);
    changeEntry(M, 1, 2, 2);
    changeEntry(M, 1, 3, 3);
    changeEntry(M, 2, 1, 1);
    changeEntry(M, 2, 2, 1);
    changeEntry(M, 2, 3, 4);
    changeEntry(M, 3, 1, 1);
    changeEntry(M, 3, 2, 1);
    changeEntry(M, 3, 3, 1);

    printMatrix(stdout, M);
    printf("%d\n", size(M));
    printf("%d\n", NNZ(M));

    changeEntry(M, 2, 2, 0);
    changeEntry(M, 1, 1, 0);
    printMatrix(stdout, M);
    printf("%d\n", NNZ(M));

    printf("Copy:\n");
    Matrix A = copy(M);
    printMatrix(stdout, A);
    printf("%s\n", equals(M, A) ? "true" : "false");

    printf("Transpose:\n");
    Matrix B = transpose(M);
    printMatrix(stdout, B);
    printf("%s\n", equals(M, B) ? "true" : "false");

    printf("Matrix B before makeZero():\n");
    printMatrix(stdout, B);
    makeZero(B);
    printf("Matrix B after makeZero():\n");
    printMatrix(stdout, B);
    printf("size(B): %d\n", size(B));
    printf("nnz(B): %d\n", NNZ(B));

    printf("scalarMult(A, 1.2):\n");
    Matrix P = scalarMult(1.2, A);
    printMatrix(stdout, P);

    freeMatrix(&M);
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&P);

    printf("\033[0m"); // Reset output color

    // Run provided test from MatrixClient.c
    printf("\nRunning the provided MatrixClient test:\n\n");
    MatrixClient();
    printf("\n");

    return 0;
}

void MatrixClient() {
    int n = 100000;
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    Matrix C, D, E, F, G, H;

    changeEntry(A, 1, 1, 1);
    changeEntry(B, 1, 1, 1);
    changeEntry(A, 1, 2, 2);
    changeEntry(B, 1, 2, 0);
    changeEntry(A, 1, 3, 3);
    changeEntry(B, 1, 3, 1);
    changeEntry(A, 2, 1, 4);
    changeEntry(B, 2, 1, 0);
    changeEntry(A, 2, 2, 5);
    changeEntry(B, 2, 2, 1);
    changeEntry(A, 2, 3, 6);
    changeEntry(B, 2, 3, 0);
    changeEntry(A, 3, 1, 7);
    changeEntry(B, 3, 1, 1);
    changeEntry(A, 3, 2, 8);
    changeEntry(B, 3, 2, 1);
    changeEntry(A, 3, 3, 9);
    changeEntry(B, 3, 3, 1);

    printf("%d\n", NNZ(A));
    printMatrix(stdout, A);
    printf("\n");

    printf("%d\n", NNZ(B));
    printMatrix(stdout, B);
    printf("\n");

    C = scalarMult(1.5, A);
    printf("%d\n", NNZ(C));
    printMatrix(stdout, C);
    printf("\n");

    D = sum(A, B);
    printf("%d\n", NNZ(D));
    printMatrix(stdout, D);
    printf("\n");

    E = diff(A, A);
    printf("%d\n", NNZ(E));
    printMatrix(stdout, E);
    printf("\n");

    F = transpose(B);
    printf("%d\n", NNZ(F));
    printMatrix(stdout, F);
    printf("\n");

    G = product(B, B);
    printf("%d\n", NNZ(G));
    printMatrix(stdout, G);
    printf("\n");

    H = copy(A);
    printf("%d\n", NNZ(H));
    printMatrix(stdout, H);
    printf("\n");

    printf("%s\n", equals(A, H) ? "true" : "false");
    printf("%s\n", equals(A, B) ? "true" : "false");
    printf("%s\n", equals(A, A) ? "true" : "false");

    makeZero(A);
    printf("%d\n", NNZ(A));
    printMatrix(stdout, A);

    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);

    /*
    Output of this program:
    9
    1: (1, 1.0) (2, 2.0) (3, 3.0)
    2: (1, 4.0) (2, 5.0) (3, 6.0)
    3: (1, 7.0) (2, 8.0) (3, 9.0)

    6
    1: (1, 1.0) (3, 1.0)
    2: (2, 1.0)
    3: (1, 1.0) (2, 1.0) (3, 1.0)

    9
    1: (1, 1.5) (2, 3.0) (3, 4.5)
    2: (1, 6.0) (2, 7.5) (3, 9.0)
    3: (1, 10.5) (2, 12.0) (3, 13.5)

    9
    1: (1, 2.0) (2, 2.0) (3, 4.0)
    2: (1, 4.0) (2, 6.0) (3, 6.0)
    3: (1, 8.0) (2, 9.0) (3, 10.0)

    0

    6
    1: (1, 1.0) (3, 1.0)
    2: (2, 1.0) (3, 1.0)
    3: (1, 1.0) (3, 1.0)

    7
    1: (1, 2.0) (2, 1.0) (3, 2.0)
    2: (2, 1.0)
    3: (1, 2.0) (2, 2.0) (3, 2.0)

    9
    1: (1, 1.0) (2, 2.0) (3, 3.0)
    2: (1, 4.0) (2, 5.0) (3, 6.0)
    3: (1, 7.0) (2, 8.0) (3, 9.0)

    true
    false
    true
    0
    */
}
