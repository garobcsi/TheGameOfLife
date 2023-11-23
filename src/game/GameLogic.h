#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "FileHandlerStruct.h"
#include "../terminal/WindowSize.h"

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
    int x,y;
} Point;


Matrix * InitializeMatrix(SizeMatrix size);
void DestroyMatrix(Matrix * matrix);
Game * InitializeGame();
void DestroyGame(Game * game);
void DeleteGameData (Game * game);
int NextStep(Matrix ** matrix);

#endif