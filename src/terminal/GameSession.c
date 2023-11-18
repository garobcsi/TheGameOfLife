#include <stdlib.h>
#include <stdio.h>
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
    game->winSize = GetWindowSize();

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
        free(str);
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

    PrintGameMenu();
    // TODO: menu : quit, save, next, set (x,y)
    switch (PromptGameMenu()) {
        case 1: // Next Step
            HandleGameNextStep(game);
            break;
        case 2: // Kill / Revive
            HandleGameModify(game);
            break;
        case 3: // Randomize
            HandleGameRandomize(game);
            break;
        case 4: // Clear
            HandleGameClear(game);
            break;
        case 5: // Save
            HandleGameSave(game);
            break;
        case 8: // Back
            HandleGameBack(game);
            break;
        case 9: // Exit
            HandleGameQuit(game);
            break;

    }
    return;
}

void HandleGameNextStep(Game * game) {
    game->fileProps.didUserSave = false;

    LoadMenu(mainGame,game);
}

void HandleGameModify(Game * game) {
    game->fileProps.didUserSave = false;

    LoadMenu(mainGame,game);
}

void HandleGameRandomize(Game * game) {
    game->fileProps.didUserSave = false;

    bool yn = false;
    while (true) {
        ClearScr();
        PrintHeader("Randomize\n");
        int error = PromptYesNo(&yn,"This will rewrite game save data!\n\nDo you want to continue [y/n]");
        if (error == 3) {
            LoadMenu(abortGame,game);
        }
        if (error == 0) {
            break;
        }
    }
    if (yn) {
        for (int i = 0; i < (int)game->matrix->size.y; ++i) {
            for (int j = 0; j < (int) game->matrix->size.x; ++j)
                game->matrix->data[j][i] = (bool)(rand() % 2);
        }
    }
    LoadMenu(mainGame,game);
}

void HandleGameClear(Game * game) {
    game->fileProps.didUserSave = true;

    bool yn = false;
    while (true) {
        ClearScr();
        PrintHeader("Game Clear\n");
        int error = PromptYesNo(&yn,"This will clear your game!\n\nDo you want to continue [y/n]");
        if (error == 3) {
            LoadMenu(abortGame,game);
        }
        if (error == 0) {
            break;
        }
    }
    if (yn) {
        for (int i = 0; i < (int)game->matrix->size.y; ++i) {
            for (int j = 0; j < (int) game->matrix->size.x; ++j)
                game->matrix->data[j][i] = false;
        }
    }
    LoadMenu(mainGame,game);
}

void HandleGameSave(Game * game) {
    game->fileProps.didUserSave = true;

    int error =  SaveMatrixToFile(game->matrix,game->fileProps.name);
    if (error == 1) {
        LoadMenu(abortGame,game);
    }
    ClearScr();
    PrintHeader("Game Save\n");
    PrintGameWasSaved();
    SleepTime(1);
    LoadMenu(mainGame,game);
}

void HandleDoYouWantToSave(Game * game) {
    ClearScr();
    PrintHeader("Game Save\n");
    bool yn = false;
    int promptError = PromptYesNo(&yn,"Do you want to save your game [y/n]");
    if (promptError == 3) {
        LoadMenu(abortGame,game);
    }
    if (yn) {
        int fileError =  SaveMatrixToFile(game->matrix,game->fileProps.name);
        if (fileError == 1) {
            LoadMenu(abortGame,game);
        }
    }
}

void HandleGameBack(Game * game) {
    if (game->fileProps.didUserSave == false) HandleDoYouWantToSave(game);
    DeleteGameData(game);
    LoadMenu(mainMenu,game);
}

void HandleGameQuit(Game * game) {
    if (game->fileProps.didUserSave == false) HandleDoYouWantToSave(game);
}