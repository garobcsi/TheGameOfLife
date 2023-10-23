#include <time.h>
#include <stdlib.h>
#include <unistd.h>

void InitRandom() {
    unsigned int seed = 0;

    seed ^= (unsigned)time(NULL);
    seed ^= (unsigned)time(NULL) << 16;
    seed ^= (unsigned)getpid();

    srand(seed);
}