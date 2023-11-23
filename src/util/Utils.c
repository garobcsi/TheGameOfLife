#include "../../debugmalloc.h"
#include "../terminal/StyleHandler.h"

#ifdef _WIN32
#include <Windows.h>
#endif

void AbortMsg(char str[]) {
    AnsiColorRed();
    printf("\n%s\n",str);
    AnsiResetAll();
}
void SleepTime(int time) {
#ifdef _WIN32
    Sleep(time *1000);
#else
    sleep(time);
#endif
}