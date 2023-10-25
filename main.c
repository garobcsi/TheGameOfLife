#include "src/game/FileHandler.h"
#include "src/game/Random.h"
#include "src/terminal/GameSession.h"
#include "src/terminal/PrintHandler.h"
#include "src/terminal/WindowSize.h"
#include "debugmalloc.h"

int main() {
    InitSaveFolder();
    InitRandom();

    #ifdef _WIN32
    InitPrintUTF8ForWindows();
    #endif

    ClearScr();

    WindowSize * winSize = GetWindowSize();
    StartTerminalSession(winSize);


    DestroyWindowSize(winSize);
    return 0;
}
