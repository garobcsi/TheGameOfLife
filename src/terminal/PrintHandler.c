#include <stdio.h>
#include <stdlib.h>
#include "PrintHandler.h"
#include "StyleHandler.h"
#include "../game/MathHandler.h"

void PrintBoxTop(int indent,int cellsX) {
    for (int i = 0; i < indent; ++i) {
        printf(" ");
    }
    printf("+");
    for (int i = 0; i < cellsX; ++i) {
        printf("--");
    }
    printf("+\n");
}

void MatrixBoard(Matrix * game) {
    int sizeY = IntSize((int)game->size.y);

    PrintBoxTop(sizeY,(int)game->size.x);
    for (int i = 0; i < game->size.y; ++i) {
        for (int j = 0; j < game->size.x; ++j) {
            if(j==0) printf("%0*d|",sizeY,i+1);
            if (game->matrix[j][i]) BackgorundWhite();
            printf("  ");
            ResetAll();
        }
        printf("|");
        printf("\n");
    }
    PrintBoxTop(sizeY,(int)game->size.x);
}

void ClearScr() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
