#include "src/game/FileHandler.h"
#include "src/game/Random.h"
#include "src/terminal/GameSession.h"
#include "src/terminal/PrintHandler.h"
#include "debugmalloc.h"

int main() {
    InitSaveFolder();
    InitRandom();

    #ifdef _WIN32
    InitPrintUTF8ForWindows();
    #endif

    ClearScr();

    WinSize winSize = GetWindowSize();
    StartTerminalSession(winSize);
    return 0;
}
