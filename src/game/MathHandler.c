#include <stdlib.h>
#include <math.h>

int IntSize(int num) {
    int absolute = abs(num);
    double lenght = log10(absolute);
    int convert = floor(lenght);
    return convert+1;
}