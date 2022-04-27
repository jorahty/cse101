// James Tennant • jtennant • pa4

#include "Matrix.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// ██ Private Types ██

// Define private MatrixObj type
typedef struct MatrixObj {
    List* A;
    int size;
    int nnz;
} MatrixObj;

// Define private Entry type
typedef struct EntryObj* Entry;

// Define private EntryObj type
typedef struct EntryObj {
   int col;
   int val;
} EntryObj;

// ██ Constructors & Destructors ██

Matrix newMatrix();
void freeMatrix(Matrix* pM);

// ██ Access Functions ██

// ██ Manipulation Procedures ██

// ██ Other Functions ██

void printMatrix(FILE* out, Matrix M);
