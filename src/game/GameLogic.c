#include <stdbool.h>
#include "GameLogic.h"
#include "../util/Utils.h"
#include "../../debugmalloc.h"

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
    matrix = NULL;
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
    game->fileProps.didUserSave = true;
    return game;
}
void DestroyGame(Game * game) {
    if (game->matrix != NULL) DestroyMatrix(game->matrix);
    free(game);
    game = NULL;
}

void DeleteGameData (Game * game) {
    if (game->matrix != NULL) DestroyMatrix(game->matrix);
    game->matrix = NULL;
    game->winSize.x = 0;
    game->winSize.y = 0;
    game->fileProps.didUserSave = true;
    game->fileProps.name[0] = '\0';
}

/*
 * 0 ok
 * 1 critical error
 */
/*
 * -1,-1    +0,-1   +1,-1
 * -1,+0    +0,+0   +1,+0
 * -1,+1    +0,+1   +1,+1
 */
int FindNeighbors(Matrix * matrix,Point point) {
    int count = 0;

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }

            int x = (int)point.x + i;
            int y = (int)point.y + j;

            if (x >= 0 && x < matrix->size.x && y >= 0 && y < matrix->size.y) {
                count += matrix->data[x][y];
                if (count >= 4) {
                    return count;
                }
            }
        }
    }
    return count;
}

int NextStep(Matrix ** matrix) {
    Matrix * this = (*matrix);
    Matrix * next = InitializeMatrix(this->size);
    if (next == NULL) {
        return 1;
    }
    for (int i = 0; i < (int)this->size.y; ++i) {
        for (int j = 0; j < (int) this->size.x; ++j) {
            int n = FindNeighbors(this,(Point){j,i});

            if (this->data[j][i] == true && n<=1) {
                next->data[j][i] = false;
            } else if (this->data[j][i] == true && (n == 2 || n == 3)) {
                next->data[j][i] = true;
            } else if (this->data[j][i] == true && n>=4) {
                next->data[j][i] = false;
            } else if (this->data[j][i] == false && n== 3) {
                next->data[j][i] = true;
            }

        }
    }

    DestroyMatrix(*matrix);
    *matrix = next;
    return 0;
}