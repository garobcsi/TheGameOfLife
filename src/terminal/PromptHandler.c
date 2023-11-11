#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "StyleHandler.h"
#include "PrintHandler.h"
#include "GameSession.h"
#include "../util/Utils.h"
#include "../game/IntLogicHandler.h"
#include "../game/GameLogic.h"
#include "../game/FileHandler.h"
#include "../../debugmalloc.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

void PurgeStdin() {
int c;
while ((c = getchar()) != '\n' && c != EOF);
}

/*It will read a char without enter*/
char ReadChar() {
    char c;

#ifdef _WIN32
    c = getch();
#else
    struct termios old_term, new_term;
    tcgetattr(STDIN_FILENO, &old_term);
    new_term = old_term;
    new_term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);

    c = (char)getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
#endif

    return c;
}

int PromptMainMenu() {
    printf("\nChoose: ");
    while (true) {
        char c = ReadChar();
        int num = c-'0';
        if (isdigit(c) && ((num>=1 && num<=2) || num == 9)) {
            printf("%c\n",c);
            return num;
        }
    }
}

/*
 * 0 ok
 * 1 format error
 * 2 file name too large
 * 3 file exits
 * 4 critical error
 * */
int PromptFileName(char * str) {
    printf("Save Name: ");

    char * stdinError = fgets(str, FILE_NAME_LENGTH, stdin);
    if (stdinError == NULL) {
        AbortMsg("Failed to read input!");
        return 4;
    }
    printf("\n");

    if (str[strlen(str)-1] != '\n') {

        PurgeStdin();
        return 2;
    }
    if (strcmp(str,"\n") == 0 || FileNameHasBadChar(str)) {
        return 1;
    }
    str[strlen(str)-1] = '\0'; // remove '\n' at the end
    if (DoesFileExist(str)) {
        return 3;
    }

    return 0;
}

SizeMatrix PromptMatrixSize(Game * game) {
    int x=-1,y=-1;

    bool gotErrorX=false,gotErrorY=false;
    while (x == -1) {
        x = -1;

        printf("Game board width: ");
        bool error = scanf("%d",&x) != 1;
        //recalculate
        game->winSize = GetWindowSize();

        if (error) {
            if(gotErrorX) {
                EraseInLine();
                MoveCursorUp(1);
                EraseInLine();
            }
            MoveCursorUp(1);
            EraseInLine();
            gotErrorX=true;

            printf("Invalid input !\n");
            PurgeStdin();
            continue;
        }
        if(IsXTooBig(game->winSize,x)) {
            if(gotErrorX) {
                EraseInLine();
                MoveCursorUp(1);
                EraseInLine();
            }
            MoveCursorUp(1);
            EraseInLine();
            gotErrorX=true;

            printf("Width is too large !\n");
            x = -1;
        }
    }
    printf("\n");
    while (y == -1) {
        y = -1;

        printf("Game board height: ");
        bool error = scanf("%d",&y) != 1;
        //recalculate
        game->winSize = GetWindowSize();
        if (error) {
            if(gotErrorY) {
                EraseInLine();
                MoveCursorUp(1);
                EraseInLine();
            }
            MoveCursorUp(1);
            EraseInLine();
            gotErrorY=true;

            printf("Invalid input !\n");
            PurgeStdin();
            continue;
        }

        if(IsYTooBig(game->winSize,y)) {
            if(gotErrorY) {
                EraseInLine();
                MoveCursorUp(1);
                EraseInLine();
            }
            MoveCursorUp(1);
            EraseInLine();
            gotErrorY=true;

            printf("Height is too large !\n");
            y = -1;
        }
    }

    return (SizeMatrix){x,y};
}