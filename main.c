#include "src/game/FileHandler.h"
#include "src/game/Random.h"
#include "src/terminal/GameSession.h"
#include "debugmalloc.h"

int main() {
    InitSaveFolder();
    InitRandom();
    StartTerminalSession();

    return 0;
}
