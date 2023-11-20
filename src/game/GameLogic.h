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
    GameFileProperties fileProps;
} Game;

typedef struct Point {
    size_t x,y;
} Point;

#endif /* GAME_LOGIC */

Matrix * InitializeMatrix(SizeMatrix size);
void DestroyMatrix(Matrix * matrix);
Game * InitializeGame();
void DestroyGame(Game * game);
void DeleteGameData (Game * game);
int NextStep(Matrix ** matrix);