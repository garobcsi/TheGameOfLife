#include <sys/ioctl.h>
#include <unistd.h>
#include "WindowSize.h"
#include "../../debugmalloc.h"
#include "../util/Utils.h"

/*
 * It's using malloc IT HAS TO BE FREED
 * Use "DestroyWindowSize" Function
 * */
WindowSize *GetWindowSize() {
    WindowSize *w = (WindowSize *)malloc(sizeof(WindowSize));
    if(w == NULL) {
        AbortMsg("Memory allocation failed!");
        return NULL;
    }
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, w) == -1) {
        free(w); // Free the allocated memory in case of an error
        AbortMsg("Failed To Get Terminal Size!");
        return NULL;
    }

    return w;
}

void DestroyWindowSize(WindowSize * windowSize) {
    free(windowSize);
}