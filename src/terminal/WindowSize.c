#include "WindowSize.h"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

WinSize GetWindowSize() {
    WinSize tmp;
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