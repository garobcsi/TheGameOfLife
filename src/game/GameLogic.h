#include <stddef.h>
#include <stdbool.h>
#include "../terminal/WindowSize.h"
#include "FileHandlerStruct.h"

#ifndef GAME_LOGIC
#define GAME_LOGIC

typedef struct SizeMatrix {
    size_t x,y;
} SizeMatrix;

typedef struct Matrix {
    struct SizeMatrix size;
    bool ** data;
} Matrix;

typedef struct Game {
    Matrix * matrix;
    WinSize winSize;
    LoadedFileProperties fileProps;
} Game;

#endif /* GAME_LOGIC */

Matrix * InitializeMatrix(SizeMatrix size);
void DestroyMatrix(Matrix * matrix);
Game * InitializeGame();
void DestroyGame(Game * game);
