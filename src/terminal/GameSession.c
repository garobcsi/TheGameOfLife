#include "PrintHandler.h"
#include "PromptHandler.h"

void StartTerminalSession(WinSize winSize) {
    PrintLogo(winSize);
    PrintMainMenu();
}