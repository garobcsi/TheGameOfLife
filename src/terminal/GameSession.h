#ifndef GAME_SESSION_H
#define GAME_SESSION_H

#define MAX_X 255
#define MAX_Y 255

#ifdef _WIN32

#define ARROW_LEFT 75
#define ARROW_RIGHT 77
#define ARROW_UP 72
#define ARROW_DOWN 80

#else

#define ARROW_LEFT 68
#define ARROW_RIGHT 67
#define ARROW_UP 65
#define ARROW_DOWN 66

#endif

#include "WindowSize.h"
#include "../game/GameLogic.h"


typedef enum { mainMenu,newGame,loadGame,mainGame,abortGame } MenuOption;


int  LoadMenu(MenuOption menuOption,Game * game);
void HandleMainMenu(Game * game);
void HandleNewGame(Game * game);
void HandleLoadGame(Game * game);
void HandleMainGame(Game * game);

void HandleGameNextStep(Game * game);
void HandleGameModify(Game * game);
void HandleGameRandomize(Game * game);
void HandleGameClear(Game * game);
void HandleGameSave(Game * game);
void HandleGameBack(Game * game);
void HandleGameQuit(Game * game);

#endif