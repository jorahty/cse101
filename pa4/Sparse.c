// James Tennant • jtennant • pa4

#include "Matrix.h"
#include <stdbool.h>
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

    // Get first line
    int n, a, b;
    fscanf(in, "%d %d %d\n", &n, &a, &b); // Get n, a, b
    fscanf(in, "\n");

    // Construct & print Matrix A
    Matrix A = newMatrix(n);
    for (int i = 0; i < a; i++) {
        int i, j;
        double x;
        fscanf(in, "%d %d %lf\n", &i, &j, &x);
        changeEntry(A, i, j, x);
    }
    fprintf(out, "A has %d non-zero entries:\n", a);
    printMatrix(out, A);
    fprintf(out, "\n");

    // Construct & print Matrix B
    Matrix B = newMatrix(n);
    for (int i = 0; i < a; i++) {
        int i, j;
        double x;
        fscanf(in, "%d %d %lf\n", &i, &j, &x);
        changeEntry(B, i, j, x);
    }
    fprintf(out, "B has %d non-zero entries:\n", b);
    printMatrix(out, B);
    fprintf(out, "\n");

    // 1.5 * A
    Matrix C = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, C);
    fprintf(out, "\n");

    // A + B
    Matrix D = sum(A, B);
    fprintf(out, "A+B =\n");
    printMatrix(out, D);
    fprintf(out, "\n");

    // A + A
    Matrix E = sum(A, A);
    fprintf(out, "A+A =\n");
    printMatrix(out, E);
    fprintf(out, "\n");

    // B - A
    Matrix F = diff(B, A);
    fprintf(out, "B-A =\n");
    printMatrix(out, F);
    fprintf(out, "\n");

    // A - A
    Matrix G = diff(A, A);
    fprintf(out, "A-A =\n");
    printMatrix(out, G);
    fprintf(out, "\n");

    // Transpose(A)
    Matrix H = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, H);
    fprintf(out, "\n");

    // A*B
    Matrix I = product(A, B);
    fprintf(out, "A*B =\n");
    printMatrix(out, I);
    fprintf(out, "\n");

    // B*B
    Matrix J = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, J);
    fprintf(out, "\n");

    // Free memory
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);

    // Close files
    fclose(in);
    fclose(out);

    return 0;
}
