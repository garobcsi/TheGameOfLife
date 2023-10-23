#include <stdio.h>
#include <stdlib.h>
#include "PrintHandler.h"
#include "StyleHandler.h"
#include "../game/IntLogicHandler.h"

#ifdef _WIN32
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

void PrintMatrixBoard(Matrix * data) {
    int sizeY = IntDigitSize((int)data->size.y);

    PrintBoxTop((int)data->size.x,sizeY);
    for (int i = 0; i < data->size.y; ++i) {
        for (int j = 0; j < data->size.x; ++j) {
            if(j==0) printf("%0*d|",sizeY,i+1);
            if (data->matrix[j][i]) AnsiBackgroundWhite();
            printf("  ");
            AnsiResetAll();
        }
        printf("|");
        printf("\n");
    }
    PrintBoxTop((int)data->size.x,sizeY);
    PrintNumbersVertically((int)data->size.x,sizeY);
    printf("\n");
}

void ClearScr() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void PrintLogo() {
    // #CREDIT: https://patorjk.com/software/taag/#p=display&h=0&v=0&f=ANSI%20Shadow&t=The%20Game%20Of%20Life
    printf("\n"
           "████████╗██╗  ██╗███████╗     ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ███████╗    ██╗     ██╗███████╗███████╗\n"
           "╚══██╔══╝██║  ██║██╔════╝    ██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██╔════╝    ██║     ██║██╔════╝██╔════╝\n"
           "   ██║   ███████║█████╗      ██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║█████╗      ██║     ██║█████╗  █████╗  \n"
           "   ██║   ██╔══██║██╔══╝      ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║██╔══╝      ██║     ██║██╔══╝  ██╔══╝  \n"
           "   ██║   ██║  ██║███████╗    ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝██║         ███████╗██║██║     ███████╗\n"
           "   ╚═╝   ╚═╝  ╚═╝╚══════╝     ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝ ╚═╝         ╚══════╝╚═╝╚═╝     ╚══════╝\n");
}

