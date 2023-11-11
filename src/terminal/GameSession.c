#include "GameSession.h"
#include "PrintHandler.h"
#include "PromptHandler.h"
#include "PrintHandler.h"
#include "../util/Utils.h"
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
    ClearScr();

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
    if (str == NULL) {
        LoadMenu(abortGame,game);
        return;
    }
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
    strcpy(game->fileProps.name,str);
    free(str);

    SizeMatrix size = PromptMatrixSize(game);
    game->matrix = InitializeMatrix(size);

    if (game->matrix == NULL) {
        AbortMsg("Matrix were not initialized!");
        LoadMenu(abortGame,game);
        return;
    }

    int fileError = SaveMatrixToFile(game->matrix,game->fileProps.name);
    if (fileError == 1) {
        LoadMenu(abortGame,game);
        return;
    }

    LoadMenu(mainGame,game);
    return;
}
void HandleLoadGame(Game * game) {
    ClearScr();
    PrintHeader("Load Game");
    printf("\n");

    GameSaveFiles * files = NULL;
    int errorFile = GetSaveFiles(&files);
    if (errorFile == 1) {
        LoadMenu(abortGame,game);
        return;
    }
    if (files->count == 0) {
        printf("No saves were found!\n\n");
        PrintBack();
        PromptBack();
        DestroyStructSaveFiles(files);
        LoadMenu(mainMenu,game);
        return;
    }
    PrintFiles(files);
    int select = -1;
    int errorSelect = PromptFileLoad(&select,files,game);
    if (errorSelect == 1) {
        DestroyStructSaveFiles(files);
        LoadMenu(abortGame,game);
        return;
    }
    SizeMatrix size = {0,0};
    int errorSizeFile = GetSizeFromFile(&size,files,select);
    if (errorSizeFile == 1) {
        DestroyStructSaveFiles(files);
        LoadMenu(abortGame,game);
        return;
    }
    if (size.x == 0 && size.y == 0) {
        AbortMsg("Failed to get matrix size from file !");
        DestroyStructSaveFiles(files);
        LoadMenu(abortGame,game);
        return;
    }
    game->matrix = InitializeMatrix(size);

    int errorMatrixLoad = LoadGameFromFile(game,files,select);
    if (errorMatrixLoad == 1) {
        DestroyStructSaveFiles(files);
        LoadMenu(abortGame,game);
        return;
    }

    DestroyStructSaveFiles(files);

    if (game->matrix == NULL) {
        AbortMsg("Matrix were not initialized!");
        LoadMenu(abortGame,game);
        return;
    }

    LoadMenu(mainGame,game);
    return;
}
void HandleMainGame(Game * game) {
    ClearScr();

    PrintHeader("The Game Of Life");
    printf("\n");

    PrintMatrixBoard(game->matrix);
}
void HandleQuit(Game * game) {

}