#include "src/game/FileHandler.h"
#include "src/game/Random.h"
#include "src/terminal/GameSession.h"
#include "src/terminal/PrintHandler.h"
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
        return 1; // error while creating (malloc) game
    }

    int abortStatus = LoadMenu(mainMenu,game);

    DestroyGame(game);

    if (abortStatus == 1) {
        return 1; // after destroying game return with error
    }

    return 0;
}
