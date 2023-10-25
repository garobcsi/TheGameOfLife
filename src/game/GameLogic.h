#include <stddef.h>
#include <stdbool.h>

typedef struct SizeMatrix {
    size_t x,y;
} SizeMatrix;

typedef struct Matrix {
    struct SizeMatrix size;
    bool ** matrix;
} Matrix;

Matrix * InitializeMatrix(SizeMatrix size);
void DestroyMatrix(Matrix * data);