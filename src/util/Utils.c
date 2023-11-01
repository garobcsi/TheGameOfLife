#include <stdio.h>
#include "../terminal/StyleHandler.h"

void AbortMsg(char str[]) {
    AnsiColorRed();
    printf("\n%s\n",str);
    AnsiResetAll();
}