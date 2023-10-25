#include "WindowSize.h"
#include "../game/GameLogic.h"

#ifdef _WIN32
void InitPrintUTF8ForWindows();
#endif

void PrintMatrixBoard(Matrix * data);
void ClearScr();

void PrintLogo(WindowSize * windowSize);