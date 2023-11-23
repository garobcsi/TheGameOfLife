#include <time.h>
#include <stdlib.h>
#include "../../debugmalloc.h"

#ifdef __linux__ 
#include <unistd.h>
#endif

void InitRandom() {
    unsigned int seed = 0;

    seed ^= (unsigned)time(NULL);
    seed ^= (unsigned)time(NULL) << 16;
    seed ^= (unsigned)getpid();

    srand(seed);
}