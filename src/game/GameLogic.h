#include <stddef.h>
#include <stdbool.h>

#ifndef GAME_LOGIC
#define GAME_LOGIC

typedef struct SizeMatrix {
    size_t x,y;
} SizeMatrix;

typedef struct Matrix {
    struct SizeMatrix size;
    bool ** data;
} Matrix;

#endif /* GAME_LOGIC */

Matrix * InitializeMatrix(SizeMatrix size);
void DestroyMatrix(Matrix * matrix);