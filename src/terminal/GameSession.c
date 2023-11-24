#include "../../debugmalloc.h"
#include "GameSession.h"
#include "PrintHandler.h"
#include "PromptHandler.h"
#include "../util/Utils.h"
#include "../game/FileHandler.h"

Menu MainMenu(Menu menu,Game * game) {
    do {
        switch (menu) {
            case MENU_INIT: {
                DeleteGameData(game);
                ClearScr();
                game->winSize = GetWindowSize();
                PrintLogo(game->winSize);
                PrintMainMenu();
                int select = PromptMainMenu();
                switch (select) {
                    case 1:
                        menu = NewGame(MENU_INIT, game);
                        continue;
                        break;
                    case 2:
                        menu = LoadGame(MENU_INIT, game);
                        continue;
                        break;
                    case 9:
                        return MENU_EXIT;
                        break;
                    default:
                        continue;
                        break;
                }
                continue;
                break;
            }
            case MENU_BACK:
                menu = MENU_INIT;
                continue;
                break;
            case MENU_ABORT:
                return MENU_ABORT;
                break;
            case MENU_EXIT:
                return MENU_EXIT;
                break;
        }
    } while (true);
    return MENU_BACK;
}

Menu NewGame(Menu menu,Game * game) {
    do {
        switch (menu) {
            case MENU_INIT: {
                int saveError = 0;
                char str[FILE_NAME_LENGTH+1];
                str[0] = '\0';
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
                        return MENU_ABORT;
                    }
                } while (saveError != 0);

                strcpy(game->fileProps.name,str);

                SizeMatrix size = PromptMatrixSize(game);
                game->matrix = InitializeMatrix(size);

                if (game->matrix == NULL) {
                    AbortMsg("Matrix were not initialized!");
                    return MENU_ABORT;
                }

                int fileError = SaveMatrixToFile(game->matrix,game->fileProps.name);
                if (fileError == 1) {
                    return MENU_ABORT;
                }

                menu = MainGame(MENU_INIT,game);
                continue;
                break;
            }
            case MENU_BACK:
                return MENU_BACK;
                break;
            case MENU_ABORT:
                return MENU_ABORT;
                break;
            case MENU_EXIT:
                return MENU_EXIT;
                break;
        }
    } while (true);
    return MENU_BACK;
}

Menu LoadGame(Menu menu,Game * game) {
    do {
        switch (menu) {
            case MENU_INIT: {
                ClearScr();
                PrintHeader("Load Game");
                printf("\n");

                GameSaveFiles * files = NULL;
                int errorFile = GetSaveFiles(&files);
                if (errorFile == 1) {
                    return MENU_ABORT;
                }
                if (files->count == 0) {
                    printf("No saves were found!\n\n");
                    PrintBack();
                    PromptBack();
                    DestroyStructSaveFiles(files);
                    return MENU_BACK;
                }
                PrintFiles(files);
                int select = -1;
                int errorSelect = PromptFileLoad(&select,files,game);
                if (errorSelect == 1) {
                    DestroyStructSaveFiles(files);
                    return MENU_ABORT;
                }
                SizeMatrix size = {0,0};
                int errorSizeFile = GetSizeFromFile(&size,files,select);
                if (errorSizeFile == 1) {
                    DestroyStructSaveFiles(files);
                    return MENU_ABORT;
                }
                if (size.x == 0 && size.y == 0) {
                    AbortMsg("Failed to get matrix size from file !");
                    DestroyStructSaveFiles(files);
                    return MENU_ABORT;
                }
                game->matrix = InitializeMatrix(size);

                int errorMatrixLoad = LoadGameFromFile(game,files,select);
                if (errorMatrixLoad == 1) {
                    DestroyStructSaveFiles(files);
                    return MENU_ABORT;
                }

                DestroyStructSaveFiles(files);

                if (game->matrix == NULL) {
                    AbortMsg("Matrix were not initialized!");
                    return MENU_ABORT;
                }

                menu = MainGame(MENU_INIT,game);
                continue;
                break;
            }
            case MENU_BACK:
                return MENU_BACK;
                break;
            case MENU_ABORT:
                return MENU_ABORT;
                break;
            case MENU_EXIT:
                return MENU_EXIT;
                break;
        }
    } while (true);
    return MENU_BACK;
}

Menu MainGame(Menu menu,Game * game) {
    do {
        switch (menu) {
            case MENU_INIT: {
                ClearScr();

                PrintHeader("The Game Of Life");
                printf("\n");

                PrintMatrixBoard(game->matrix);

                PrintGameMenu();

                switch (PromptGameMenu()) {
                    case 1: // Next Step
                        menu = GameNextStep(MENU_INIT,game);
                        continue;
                        break;
                    case 2: // Kill / Revive
                        menu = GameModify(MENU_INIT,game);
                        continue;
                        break;
                    case 3: // Randomize
                        menu = GameRandomize(MENU_INIT,game);
                        continue;
                        break;
                    case 4: // Clear
                        menu = GameClear(MENU_INIT,game);
                        continue;
                        break;
                    case 5: // Save
                        menu = GameSave(MENU_INIT,game);
                        continue;
                        break;
                    case 8: // Back
                        menu = GameBack(MENU_INIT,game);
                        continue;
                        break;
                    case 9: // Exit
                        menu = GameQuit(MENU_INIT,game);
                        continue;
                        break;

                }
                menu = MENU_INIT;
                continue;
                break;
            }
            case MENU_BACK:
                return MENU_BACK;
                break;
            case MENU_ABORT:
                return MENU_ABORT;
                break;
            case MENU_EXIT:
                return MENU_EXIT;
                break;
        }
    } while (true);
    return MENU_BACK;
}

Menu GameNextStep(Menu menu,Game * game) {
    do {
        switch (menu) {
            case MENU_INIT: {
                game->fileProps.didUserSave = false;

                int error = NextStep(&game->matrix);
                if (error == 1) {
                    return MENU_ABORT;
                }

                return MENU_INIT;
                break;
            }
            case MENU_BACK:
                return MENU_BACK;
                break;
            case MENU_ABORT:
                return MENU_ABORT;
                break;
            case MENU_EXIT:
                return MENU_EXIT;
                break;
        }
    } while (true);
    return MENU_INIT;
}

Menu GameModify(Menu menu,Game * game) {
    do {
        switch (menu) {
            case MENU_INIT: {
                game->fileProps.didUserSave = false;

                Point cursor = {0,0};
                do {
                    ClearScr();

                    PrintHeader("Kill / Revive");
                    printf("\n");

                    PrintMatrixBoardWithPoint(game->matrix,cursor);

                    int action = PromptCursor(&cursor,game->matrix->size);
                    if (action == 0) {
                        break;
                    }
                    if (action == 1) {
                        game->matrix->data[cursor.x][cursor.y] = !game->matrix->data[cursor.x][cursor.y];
                    }

                } while (true);

                return MENU_INIT;
                break;
            }
            case MENU_BACK:
                return MENU_BACK;
                break;
            case MENU_ABORT:
                return MENU_ABORT;
                break;
            case MENU_EXIT:
                return MENU_EXIT;
                break;
        }
    } while (true);
    return MENU_INIT;
}

Menu GameRandomize(Menu menu,Game * game) {
    do {
        switch (menu) {
            case MENU_INIT: {
                game->fileProps.didUserSave = false;

                bool yn = false;
                while (true) {
                    ClearScr();
                    PrintHeader("Randomize");
                    printf("\n");
                    int error = PromptYesNo(&yn,"This will rewrite game data!\n\nDo you want to continue [y/n]");
                    if (error == 2) {
                        return MENU_ABORT;
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

                return MENU_INIT;
                break;
            }
            case MENU_BACK:
                return MENU_BACK;
                break;
            case MENU_ABORT:
                return MENU_ABORT;
                break;
            case MENU_EXIT:
                return MENU_EXIT;
                break;
        }
    } while (true);
    return MENU_INIT;
}

Menu GameClear(Menu menu,Game * game) {
    do {
        switch (menu) {
            case MENU_INIT: {
                game->fileProps.didUserSave = false;

                bool yn = false;
                while (true) {
                    ClearScr();
                    PrintHeader("Game Clear");
                    printf("\n");
                    int error = PromptYesNo(&yn,"This will clear your game!\n\nDo you want to continue [y/n]");
                    if (error == 2) {
                        return MENU_ABORT;
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
                return MENU_INIT;
                break;
            }
            case MENU_BACK:
                return MENU_BACK;
                break;
            case MENU_ABORT:
                return MENU_ABORT;
                break;
            case MENU_EXIT:
                return MENU_EXIT;
                break;
        }
    } while (true);
    return MENU_INIT;
}

Menu GameSave(Menu menu,Game * game) {
    do {
        switch (menu) {
            case MENU_INIT: {
                game->fileProps.didUserSave = true;

                int error =  SaveMatrixToFile(game->matrix,game->fileProps.name);
                if (error == 1) {
                    return MENU_ABORT;
                }
                ClearScr();
                PrintHeader("Game Save");
                printf("\n");
                PrintGameWasSaved();
                SleepTime(1);

                return MENU_INIT;
                break;
            }
            case MENU_BACK:
                return MENU_BACK;
                break;
            case MENU_ABORT:
                return MENU_ABORT;
                break;
            case MENU_EXIT:
                return MENU_EXIT;
                break;
        }
    } while (true);
    return MENU_INIT;
}

Menu DoYouWantToSave(Menu menu,Game * game) {
    do {
        switch (menu) {
            case MENU_INIT: {
                ClearScr();
                PrintHeader("Game Save");
                printf("\n");
                bool yn = false;
                int promptError = PromptYesNo(&yn,"Do you want to save your game [y/n]");
                if (promptError == 2) {
                    return MENU_ABORT;
                }
                if (promptError != 0) {
                    menu = MENU_INIT;
                    continue;
                }
                if (yn) {
                    int fileError =  SaveMatrixToFile(game->matrix,game->fileProps.name);
                    if (fileError == 1) {
                        return MENU_ABORT;
                    }
                }
                return MENU_INIT;
                break;
            }
            case MENU_BACK:
                return MENU_BACK;
                break;
            case MENU_ABORT:
                return MENU_ABORT;
                break;
            case MENU_EXIT:
                return MENU_EXIT;
                break;
        }
    } while (true);
    return MENU_INIT;
}

Menu GameBack(Menu menu,Game * game) {
    do {
        switch (menu) {
            case MENU_INIT: {
                if (game->fileProps.didUserSave == false) {
                    menu = DoYouWantToSave(MENU_INIT,game);
                    if (menu != MENU_INIT) {
                        continue;
                    }
                }
                DeleteGameData(game);
                return MENU_BACK;
                break;
            }
            case MENU_BACK:
                return MENU_BACK;
                break;
            case MENU_ABORT:
                return MENU_ABORT;
                break;
            case MENU_EXIT:
                return MENU_EXIT;
                break;
        }
    } while (true);
    return MENU_BACK;
}

Menu GameQuit(Menu menu,Game * game) {
    do {
        switch (menu) {
            case MENU_INIT: {
                if (game->fileProps.didUserSave == false) {
                    menu = DoYouWantToSave(MENU_INIT,game);
                    if (menu != MENU_INIT) {
                        continue;
                    }
                }
                return MENU_EXIT;
                break;
            }
            case MENU_BACK:
                return MENU_BACK;
                break;
            case MENU_ABORT:
                return MENU_ABORT;
                break;
            case MENU_EXIT:
                return MENU_EXIT;
                break;
        }
    } while (true);
    return MENU_EXIT;
}