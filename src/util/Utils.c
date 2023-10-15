#include <stdio.h>
#include <stdlib.h>
#include "../terminal/StyleHandler.h"

void AbortMsg(char str[]) {
    ColorRed();
    printf("\n%s\n",str);
    ResetAll();
    exit(1);
}