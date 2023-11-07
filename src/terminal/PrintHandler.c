#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PrintHandler.h"
#include "StyleHandler.h"
#include "../game/CharLogicHandler.h"
#include "../game/IntLogicHandler.h"
#include "../game/FileHandler.h"
#include "../../debugmalloc.h"

#ifdef _WIN32
#include <windows.h>

void InitPrintUTF8ForWindows() {
    SetConsoleOutputCP(65001);
}
#endif

void PrintBoxTop(int width,int indent) {
    for (int i = 0; i < indent; ++i) {
        printf(" ");
    }
    printf("+");
    for (int i = 0; i < width; ++i) {
        printf("--");
    }
    printf("+\n");
}

void PrintNumbersVertically(int length,int indent) {
    int size = IntDigitSize(length);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < indent; ++j) {
            printf(" ");
        }
        for (int j = 0; j <= length; ++j) {
            int digit = IntGetDigitWithIndex(j,i);
            if (digit != -1) {
                printf("%d|",digit);
            } else printf(" |");
        }
        printf("\n");
    }
}

void PrintMatrixBoard(Matrix * matrix) {
    int sizeY = IntDigitSize((int)matrix->size.y);

    PrintBoxTop((int)matrix->size.x,sizeY);
    for (int i = 0; i < matrix->size.y; ++i) {
        for (int j = 0; j < matrix->size.x; ++j) {
            if(j==0) printf("%0*d|",sizeY,i+1);
            if (matrix->data[j][i]) AnsiBackgroundWhite();
            printf("  ");
            AnsiResetAll();
        }
        printf("|");
        printf("\n");
    }
    PrintBoxTop((int)matrix->size.x,sizeY);
    PrintNumbersVertically((int)matrix->size.x,sizeY);
    printf("\n");
}

void ClearScr() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void PrintHeader(char * str) {
    AnsiBackgroundWhite();
    AnsiColorBlack();
    printf("%s",str);
    AnsiResetAll();
    printf("\n");
}

void PrintLogo(WinSize winSize) {
    if(winSize.x >= 117) {
        // #CREDIT: https://patorjk.com/software/taag/#p=display&h=0&v=0&f=ANSI%20Shadow&t=The%20Game%20Of%20Life
        printf("\n"
               "████████╗██╗  ██╗███████╗     ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ███████╗    ██╗     ██╗███████╗███████╗\n"
               "╚══██╔══╝██║  ██║██╔════╝    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██╔════╝    ██║     ██║██╔════╝██╔════╝\n"
               "   ██║   ███████║█████╗      ██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║█████╗      ██║     ██║█████╗  █████╗  \n"
               "   ██║   ██╔══██║██╔══╝      ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║██╔══╝      ██║     ██║██╔══╝  ██╔══╝  \n"
               "   ██║   ██║  ██║███████╗    ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝██║         ███████╗██║██║     ███████╗\n"
               "   ╚═╝   ╚═╝  ╚═╝╚══════╝     ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝ ╚═╝         ╚══════╝╚═╝╚═╝     ╚══════╝\n\n");
    } else {
        PrintHeader("The Game Of Life");
        printf("\n");
    }
}

void PrintMainMenu() {
    PrintHeader("Main Menu");
    printf("\n");
    printf("1) New Game\n");
    printf("2) Load Game\n");
    printf("9) Exit Game\n");
}

void PrintFiles(GameSaveFiles * files) {
    for (int i = 0; i < files->count; ++i) {
        char * str = CpyStr(files->data[i]);
        str[strlen(str)-4] = '\0';
        printf("%d) %s\n",i+1,str);
        free(str);
    }
}