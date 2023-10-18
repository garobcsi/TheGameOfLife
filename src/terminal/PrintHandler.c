#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "PrintHandler.h"
#include "StyleHandler.h"
#include "../util/IntLogicHandler.h"
#include "../../debugmalloc.h"

void PrintBoxTop(int indent,int cellsX) {
    for (int i = 0; i < indent; ++i) {
        printf(" ");
    }
    printf("+");
    for (int i = 0; i < cellsX; ++i) {
        printf("--");
    }
    printf("+\n");
}

void PrintNumbersVertically(int length,int indent) {
    int size = IntDigitSize(length);

    for (int i = 0; i < size; ++i) {
        char * str = (char *) malloc(length*2*sizeof(char)+2+1);
        char *tmpStr = str;
        for (int j = 0; j <= length; ++j) {
            int digit = IntGetDigitWithIndex(j,i);
            if (digit != -1) {
                tmpStr += sprintf(tmpStr,"%d|",digit);
            } else tmpStr += sprintf(tmpStr," |");
        }
        for (int j = 0; j < indent; ++j) {
            printf(" ");
        }
        printf("%s\n",str);
        free(str);
    }
}
void PrintMatrixBoard(Matrix * data) {
    int sizeY = IntDigitSize((int)data->size.y);

    PrintBoxTop(sizeY,(int)data->size.x);
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
    PrintBoxTop(sizeY,(int)data->size.x);
    PrintNumbersVertically((int)data->size.x,2);
    printf("\n");
}

void ClearScr() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
