#include "WindowSize.h"

#ifdef _WIN32

#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

WinSize GetWindowSize() {
    WinSize tmp;
#ifdef _WIN32

#else
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    tmp.x = w.ws_col;
    tmp.y = w.ws_row;
#endif
    return tmp;
}