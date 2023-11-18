#include <stdio.h>
#include "../terminal/StyleHandler.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

void AbortMsg(char str[]) {
    AnsiColorRed();
    printf("\n%s\n",str);
    AnsiResetAll();
}
void Sleep(int time) {
#ifdef _WIN32
    Sleep(time *100);
#else
    sleep(time);
#endif
}