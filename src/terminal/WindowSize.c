#include <stdbool.h>
#include <stdio.h>
#include "WindowSize.h"
#include "../terminal/GameSession.h"
#include "../game/IntLogicHandler.h"
#include "../../debugmalloc.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

WinSize GetWindowSize() {
    WinSize tmp = {0,0 };
#ifdef _WIN32
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int ret;
    ret = GetConsoleScreenBufferInfo(GetStdHandle( STD_OUTPUT_HANDLE ),&csbi);
    tmp.x = csbi.dwSize.X;
    tmp.y = csbi.dwSize.Y;
#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    tmp.x = w.ws_col;
    tmp.y = w.ws_row;
#endif
    return tmp;
}

bool IsXTooBig(WinSize winSize,size_t x) {
    int len = IntDigitSize((int)x);
    bool isTooBig = winSize.x != 0 && (int) winSize.x - (int)(x * 2 + 2 + len) < 0;
    if (isTooBig || x > MAX_X || x < 1 ) {
        return true;
    }
    else {
        return false;
    }
}

bool IsYTooBig(WinSize winSize,size_t y) {
    int len = IntDigitSize((int)y);
    bool isTooBig = winSize.y != 0 && (int)winSize.y - ((int)y+2+len+13) < 0;
    if (isTooBig || y > MAX_Y || y < 1 ) {
        return true;
    }
    else {
        return false;
    }
}