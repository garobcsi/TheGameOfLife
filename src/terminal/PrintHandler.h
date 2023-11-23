#ifndef PRINT_HANDLER_H
#define PRINT_HANDLER_H

#include "../game/GameLogic.h"

#ifdef _WIN32
void InitPrintUTF8ForWindows();
#endif

void PrintMatrixBoard(Matrix * matrix);
void PrintMatrixBoardWithPoint(Matrix * matrix,Point point);
void ClearScr();

void PrintHeader(char * str);
void PrintLogo(WinSize winSize);
void PrintMainMenu();
void PrintFiles(GameSaveFiles * files);
void PrintBack();
void PrintGameMenu();
void PrintGameWasSaved();

#endif