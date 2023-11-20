#define MAX_X 255
#define MAX_Y 255

#define ARROW_LEFT 68
#define ARROW_RIGHT 67
#define ARROW_UP 65
#define ARROW_DOWN 66

#include "WindowSize.h"
#include "../game/GameLogic.h"

#ifndef GAME_SESSION
#define GAME_SESSION

typedef enum { mainMenu,newGame,loadGame,mainGame,abortGame } MenuOption;

#endif /* GAME_SESSION */

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