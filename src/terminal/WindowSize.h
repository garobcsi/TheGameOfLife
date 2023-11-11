#include <stddef.h>
#include <stdbool.h>

#ifndef WINDOW_SIZE
#define WINDOW_SIZE

typedef struct WinSize {
    unsigned int x,y;
} WinSize;

#endif /* WINDOW_SIZE */

WinSize GetWindowSize();
bool IsXTooBig(WinSize winSize,size_t x);
bool IsYTooBig(WinSize winSize,size_t y);