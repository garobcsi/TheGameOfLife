#include "GameLogic.h"
#include "../util/Utils.h"
#include <stdbool.h>
#include "../../debugmalloc.h"

/*
 * It's using malloc IT HAS TO BE FREED
 * Use "FreeMatrix" Function
 * */
Matrix * InitializeMatrix(SizeMatrix size) {
    Matrix *tmp = (Matrix*) malloc(sizeof(Matrix));
    if (tmp == NULL) {
        free(tmp);
        AbortMsg("Memory allocation failed!");
        return NULL;
    }

    tmp->size = size;

    tmp->matrix = (bool **) malloc(size.x * sizeof(bool*));
    if (tmp->matrix == NULL) {
        free(tmp->matrix);
        free(tmp);
        AbortMsg("Memory allocation failed!");
        return NULL;
    }

    for (size_t i = 0; i < size.x; ++i) {
        tmp->matrix[i] = (bool*) malloc(size.y * sizeof(bool));
        if (tmp->matrix[i] == NULL) {
            for (int j = 0; j < i; ++j) {
                free(tmp->matrix[j]);
            }
            free(tmp->matrix);
            free(tmp);
            AbortMsg("Memory allocation failed!");
            return NULL;
        }
    }

    for (size_t i = 0; i < size.x; i++) {
        for (size_t j = 0; j < size.y; j++) {
            tmp->matrix[i][j] = false;
        }
    }

    return tmp;
}
void FreeMatrix(Matrix * data) {
    if(data== NULL) return;

    for (size_t i = 0; i < data->size.x; i++) {
        free(data->matrix[i]);
    }

    free(data->matrix);
    free(data);
}