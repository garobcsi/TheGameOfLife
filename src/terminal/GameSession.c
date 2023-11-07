#include "GameSession.h"
#include "PrintHandler.h"
#include "PromptHandler.h"
#include "PrintHandler.h"
#include "../game/FileHandler.h"
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
    int saveError = 0;
    char * str = (char *) malloc(sizeof(char)*FILE_NAME_LENGTH);
    do {
        ClearScr();
        PrintHeader("New Game");
        printf("\n");
        if (saveError == 2) {
            printf("Save name too long !\n");
        }else if (saveError==3) {
            printf("Save already exists !\n");
        }
        saveError = PromptFileName(str);
        if (saveError == 4) {
            free(str);
            LoadMenu(abortGame,game);
            return;
        }
    } while (saveError != 0);
    strcpy(game->fileProps.fileName,str);
    free(str);

    SizeMatrix size = PromptMatrixSize(game->winSize);
    game->matrix = InitializeMatrix(size);

    int fileError = SaveMatrixToFile(game->matrix,game->fileProps.fileName);
    if (fileError >= 1) {
        LoadMenu(abortGame,game);
        return;
    }

    LoadMenu(mainGame,game);
}
void HandleLoadGame(Game * game) {

}
void HandleMainGame(Game * game) {
    SizeMatrix size = PromptMatrixSize(game->winSize);
    game->matrix = InitializeMatrix(size);

    int error = SaveMatrixToFile(game->matrix,game->fileProps.fileName);
    if (error == 1) {
        LoadMenu(abortGame,game);
        return;
    }

    ClearScr();
    PrintMatrixBoard(game->matrix);
}
void HandleQuit(Game * game) {

}