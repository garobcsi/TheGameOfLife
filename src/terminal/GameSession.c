#include "GameSession.h"
#include "PrintHandler.h"
#include "PromptHandler.h"
#include "../../debugmalloc.h"
#include <stdio.h>

int LoadMenu(MenuOption menuOption,Game * game){
    switch (menuOption) {
        case mainMenu:
            HandleMainMenu(game);
            break;
        case newGame:
            HandleNewGame(game);
            break;
        case loadGame:
            HandleLoadGame(game);
            break;
        case mainGame:
            HandleMainGame(game);
            break;
        case quitGame:
            HandleQuit(game);
            break;
        case abortGame:
            return 1;
            break;
        default:
            return 0;
            break;
    }
    return 0;
}

void HandleMainMenu(Game * game) {
    PrintLogo(game->winSize);
    PrintMainMenu();
    int select = PromptMainMenu();
    switch (select) {
        case 1:
            LoadMenu(newGame,game);
            break;
        case 2:
            LoadMenu(loadGame,game);
            break;
        default:
            return;
            break;
    }
}
void HandleNewGame(Game * game) {
    PrintNewGameTitle();
    char * str = PromptFileName();
    if(str == NULL) {
        LoadMenu(abortGame,game);
        return;
    }
    printf("\n\n%s",str);
    free(str);
}
void HandleLoadGame(Game * game) {

}
void HandleMainGame(Game * game) {

}
void HandleQuit(Game * game) {

}