// James Tennant • jtennant • pa4

#include "Matrix.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>

// ██ Public Types ██

typedef struct MatrixObj* Matrix;

// ██ Constructors & Destructors ██

Matrix newMatrix();
void freeMatrix(Matrix* pM);

// ██ Access Functions ██

// ██ Manipulation Procedures ██

// ██ Other Functions ██

void printMatrix(FILE* out, Matrix M);
