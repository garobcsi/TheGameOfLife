#include <stdlib.h>
#include <math.h>
#include "../../debugmalloc.h"

int IntDigitSize(int num) {
    int absolute = abs(num);
    double lenght = log10(absolute);
    int convert = floor(lenght);
    return convert+1;
}
int IntFindTheLargest(int const nums[],int numCount) {
    int large = nums[0];
    for (int i = 1; i < numCount; ++i) {
        if (nums[i] > large) {
            large = nums[i];
        }
    }
    return large;
}
int IntGetDigitWithIndex(int num,int index) {
    num = abs(num);
    int digit = IntDigitSize(num);
    if ( index < 0 || digit < index+1) return -1;

    int sel = (int)pow(10,abs(digit-index-1));

    return (num/ sel)%10;
}