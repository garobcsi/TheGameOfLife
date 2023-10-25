#include <sys/ioctl.h>
#include <unistd.h>

typedef struct winsize WindowSize;

WindowSize *GetWindowSize();
void DestroyWindowSize(WindowSize * windowSize);