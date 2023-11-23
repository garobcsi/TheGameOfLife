#ifndef WINDOW_SIZE_H
#define WINDOW_SIZE_H

#include <stddef.h>
#include <stdbool.h>

typedef struct WinSize {
    unsigned int x,y;
} WinSize;

WinSize GetWindowSize();
bool IsXTooBig(WinSize winSize,size_t x);
bool IsYTooBig(WinSize winSize,size_t y);

#endif