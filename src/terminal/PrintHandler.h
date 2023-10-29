#include "../game/GameLogic.h"
#include "WindowSize.h"

#ifdef _WIN32
void InitPrintUTF8ForWindows();
#endif

void PrintMatrixBoard(Matrix * matrix);
void ClearScr();

void PrintLogo(WinSize winSize);