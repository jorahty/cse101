// James Tennant • jtennant • pa4

#include "Matrix.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// ██ Private Types ██

// Define private MatrixObj type
typedef struct MatrixObj {
    List* arr;
    int size;
    int nnz;
} MatrixObj;

// Define private Entry type
typedef struct EntryObj* Entry;

// Define private EntryObj type
typedef struct EntryObj {
    int col;
    double val;
} EntryObj;

// ██ Constructors & Destructors ██

// Creates an Entry
Entry newEntry(int j, double x) {
    Entry E = malloc(sizeof(EntryObj));
    E->col = j;
    E->val = x;
    return E;
}

// Deletes an Entry
void freeEntry(Entry* pE) {
    if (pE && *pE) {
        free(*pE);
        *pE = NULL;
    }
}

// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->arr = calloc(n + 1, sizeof(List)); // [1, n]
    for (int i = 1; i <= n; i++) {
        M->arr[i] = newList();
    }
    M->size = n;
    M->nnz = 0;
    return M;
}

// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
    if (pM && *pM) {
        if ((*pM)->arr) {
            for (int i = 1; i <= (*pM)->size; i++) {

                List L = (*pM)->arr[i];
                for (moveFront(L); index(L) != -1; moveNext(L)) {
                    Entry E = get(L);
                    freeEntry(&E); // Free Entry
                }

                freeList(&((*pM)->arr[i])); // Free List
            }
            free((*pM)->arr); // Free array of Lists
        }
        free(*pM); // Free Matrix
        *pM = NULL;
    }
}

// ██ Access Functions ██

// Return the size of square Matrix M.
int size(Matrix M) {
    return M->size;
}

// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
    return M->nnz;
}

// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
    if (A->size != B->size) return 0;

    // Search for inequality
    for (int i = 1; i <= A->size; i++) {
        List X = A->arr[i];
        List Y = B->arr[i];
        if (length(X) != length(Y)) return 0;

        moveFront(X);
        moveFront(Y);
        while (index(X) != -1) {
            Entry E = get(X);
            Entry F = get(Y);
            if (E->col != F->col || E->val != F->val) return 0;
            moveNext(X);
            moveNext(Y);
        }
    }

    return 1; // No inequalities found
}

// ██ Manipulation Procedures ██

// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
    for (int i = 1; i <= M->size; i++) {
        List L = M->arr[i];
        for (moveFront(L); index(L) != -1; moveNext(L)) {
            Entry E = get(L);
            freeEntry(&E); // Free Entry
        }
        clear(L);
    }
    M->nnz = 0;
}

// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
    List L = M->arr[i];
    for (moveFront(L); index(L) != -1; moveNext(L)) {
        Entry E = get(L); // For each Entry E in List L

        if (E->col == j) { // Are we at column j?
            // Mij already exists!
            // Overwrite if x ≠ 0, else delete
            if (x != 0) {
                E->val = x;
                return;
            }
            freeEntry(&E); // Must free Entry
            delete (L);
            M->nnz--;
            return;
        }

        if (E->col > j) { // Did we pass column j?
            // Mij does not exist!
            // Create Mij if x ≠ 0
            if (x != 0) {
                Entry Mij = newEntry(j, x);
                insertBefore(L, Mij);
                M->nnz++;
            }
            return;
        }
    }
    // Mij belongs at the end of List L
    // Append if x ≠ 0
    if (x != 0) {
        Entry Mij = newEntry(j, x);
        append(L, Mij);
        M->nnz++;
    }
}

// ██ Arithmetic operations ██

// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
    Matrix M = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List L = A->arr[i]; // For each List L
        for (moveFront(L); index(L) != -1; moveNext(L)) {
            Entry E = get(L); // For each Entry E
            changeEntry(M, i, E->col, E->val); // Add to M
        }
    }
    return M;
}

// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
    Matrix M = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List L = A->arr[i]; // For each List L
        for (moveFront(L); index(L) != -1; moveNext(L)) {
            Entry E = get(L); // For each Entry E
            changeEntry(M, E->col, i, E->val); // Swap i & j
        }
    }
    return M;
}

// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
    Matrix M = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List L = A->arr[i]; // For each List L
        for (moveFront(L); index(L) != -1; moveNext(L)) {
            Entry E = get(L); // For each Entry E
            changeEntry(M, i, E->col, E->val * x); // Scale the value
        }
    }
    return M;
}

// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B);

// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B);

// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B);

// ██ Other Functions ██

// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
    for (int i = 1; i <= M->size; i++) {
        List L = M->arr[i]; // For each List L
        if (length(L) == 0) continue; // Skip if empty
        fprintf(out, "%d:", i);
        for (moveFront(L); index(L) != -1; moveNext(L)) {
            Entry E = get(L); // For each Entry E
            printf(" (%d, %.1f)", E->col, E->val);
        }
        fprintf(out, "\n");
    }
}
