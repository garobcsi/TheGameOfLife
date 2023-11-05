#include "GameSession.h"
#include "PrintHandler.h"
#include "PromptHandler.h"
#include "../../debugmalloc.h"

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
    int error = 0;
    char * str = (char *) malloc(sizeof(char)*FILE_NAME_LENGTH);
    do {
        ClearScr();
        PrintNewGameTitle();
        if (error == 2) {
            printf("File Name Too Long !\n\n");
        }
        error = PromptFileName(str);
        if (error == 3) {
            LoadMenu(abortGame,game);
            return;
        }
    } while (error != 0);
    strcpy(game->fileProps.fileName,str);
    free(str);

    LoadMenu(mainGame,game);
}
void HandleLoadGame(Game * game) {

}
void HandleMainGame(Game * game) {

    SizeMatrix size = PromptMatrixSize(game->winSize);
}
void HandleQuit(Game * game) {

}