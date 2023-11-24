#include "src/game/FileHandler.h"
#include "src/game/Random.h"
#include "src/terminal/GameSession.h"
#include "debugmalloc.h"

int main() {
    int createFolderStatus = InitSaveFolder(); // create `saves` folder
    if (createFolderStatus == 1) {
        return 1; // error while creating folder
    }
    InitRandom();

    #ifdef _WIN32
    InitPrintUTF8ForWindows();
    #endif

    Game * game = InitializeGame();
    if (game == NULL) {
        DestroyGame(game);
        return 1;
    }

    Menu status = MainMenu(MENU_INIT,game);
    if (status == MENU_ABORT) {
        DestroyGame(game);
        return 1;
    }
    
    DestroyGame(game);

    return 0;
}
