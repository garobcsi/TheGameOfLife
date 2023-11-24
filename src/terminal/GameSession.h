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

#include "../game/GameLogic.h"

typedef enum Menu {
    MENU_INIT, // Start Menu
    MENU_BACK, // Go back to previous menu
    MENU_EXIT, // Exit game with return 0
    MENU_ABORT // Abort game with return 1
} Menu;

Menu MainMenu(Menu menu,Game * game);
Menu NewGame(Menu menu,Game * game);
Menu LoadGame(Menu menu,Game * game);
Menu MainGame(Menu menu,Game * game);

Menu GameNextStep(Menu menu,Game * game);
Menu GameModify(Menu menu,Game * game);
Menu GameRandomize(Menu menu,Game * game);
Menu GameClear(Menu menu,Game * game);
Menu GameSave(Menu menu,Game * game);
Menu DoYouWantToSave(Menu menu,Game * game);
Menu GameBack(Menu menu,Game * game);
Menu GameQuit(Menu menu,Game * game);

#endif