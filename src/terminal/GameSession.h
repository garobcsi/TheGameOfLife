#define X 20
#define Y 20

#define MAX_X 255
#define MAX_Y 255

#include "WindowSize.h"
#include "../game/GameLogic.h"

#ifndef GAME_SESSION
#define GAME_SESSION

typedef enum { mainMenu,newGame,loadGame,mainGame,quitGame,abortGame } MenuOption;

#endif /* GAME_SESSION */

int  LoadMenu(MenuOption menuOption,Game * game);
void HandleMainMenu(Game * game);
void HandleNewGame(Game * game);
void HandleLoadGame(Game * game);
void HandleMainGame(Game * game);
void HandleQuit(Game * game);