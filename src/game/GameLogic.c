#include <stdbool.h>
#include "GameLogic.h"
#include "../util/Utils.h"
#include "../../debugmalloc.h"

/*
 * It's using malloc IT HAS TO BE FREED
 * Use "DestroyMatrix" Function
 * */
Matrix * InitializeMatrix(SizeMatrix size) {
    Matrix *tmp = (Matrix*) malloc(sizeof(Matrix));
    if (tmp == NULL) {
        free(tmp);
        AbortMsg("Memory allocation failed!");
        return NULL;
    }

    tmp->size = size;

    tmp->data = (bool **) malloc(size.x * sizeof(bool*));
    if (tmp->data == NULL) {
        free(tmp->data);
        free(tmp);
        AbortMsg("Memory allocation failed!");
        return NULL;
    }

    for (size_t i = 0; i < size.x; ++i) {
        tmp->data[i] = (bool*) malloc(size.y * sizeof(bool));
        if (tmp->data[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(tmp->data[j]);
            }
            free(tmp->data);
            free(tmp);
            AbortMsg("Memory allocation failed!");
            return NULL;
        }
    }

    for (size_t i = 0; i < size.x; i++) {
        for (size_t j = 0; j < size.y; j++) {
            tmp->data[i][j] = false;
        }
    }

    return tmp;
}
void DestroyMatrix(Matrix * matrix) {
    if(matrix == NULL) return;

    for (size_t i = 0; i < matrix->size.x; i++) {
        free(matrix->data[i]);
    }

    free(matrix->data);
    free(matrix);
}

Game * InitializeGame() {
    Game * game = (Game*)malloc(sizeof(Game));
    if (game == NULL) {
        free(game);
        AbortMsg("Memory allocation failed!");
        return NULL;
    }
    game->matrix = NULL;
    game->winSize = GetWindowSize();
    game->fileProps.didUserSave = false;
    return game;
}
void DestroyGame(Game * game) {
    if (game->matrix != NULL) DestroyMatrix(game->matrix);
    free(game);
}