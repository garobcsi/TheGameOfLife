#include <stddef.h>
#include <stdbool.h>

typedef struct SizeMatrix {
    size_t x,y;
} SizeMatrix;

typedef struct Game {
    struct SizeMatrix size;
    bool ** matrix;
} Game;

Game * InitializeGame(SizeMatrix size);
void FreeGame(Game * game);