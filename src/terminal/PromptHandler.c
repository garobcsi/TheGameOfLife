#include "../../debugmalloc.h"
#include "StyleHandler.h"
#include "GameSession.h"
#include "../util/Utils.h"
#include "../game/FileHandler.h"

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

            printf("Width is too %s !\n",x>0? "big":"small");
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

            printf("Width is too %s !\n",y>0? "big":"small");
            y = -1;
        }
    }

    return (SizeMatrix){x,y};
}


/*
 * 0 ok
 * 1 critical error
 * */
int PromptFileLoad(int * select,GameSaveFiles * files,Game * game) {
    printf("\n");
    int num=-1;

    bool gotError=false;
    while (num == -1) {
        num = -1;

        printf("Choose: ");
        bool error = scanf("%d",&num) != 1;
        //recalculate
        game->winSize = GetWindowSize();

        bool errorInput = num <= 0 || num > files->count;
        bool errorSize = false;
        if (!errorInput) {
            SizeMatrix size = {0,0};
            int errorFile = GetSizeFromFile(&size,files,num);
            if (errorFile == 1) {
                return 1;
            }
            if (IsXTooBig(game->winSize,size.x) || IsYTooBig(game->winSize,size.y)) {
                errorSize = true;
            }
        }
        if (error || errorInput || errorSize) {
            if(gotError) {
                EraseInLine();
                MoveCursorUp(1);
                EraseInLine();
            }
            MoveCursorUp(1);
            EraseInLine();

            gotError=true;

            if (error) {
                printf("Invalid input !\n");
                PurgeStdin();
            } else if (errorInput) {
                printf("Invalid input !\n");
            } else {
                printf("Save is too big for your screen !\n");
            }
            num = -1;
        }
    }

    *select = num;
    return 0;
}

int PromptBack() {
    printf("\nChoose: ");
    while (true) {
        char c = ReadChar();
        int num = c-'0';
        if (isdigit(c) && num == 1) {
            printf("%c\n",c);
            return num;
        }
    }
}

int PromptGameMenu() {
    printf("\nChoose: ");
    while (true) {
        char c = ReadChar();
        int num = c-'0';
        if (isdigit(c) && ((num >= 1 && num <=5) || (num == 8  || num == 9)) ) {
            printf("%c\n",c);
            return num;
        }
    }
}

/*
 * 0 ok
 * 1 formatting error
 * 2 critical error
 * 3 loop
 */
int PromptYesNo(bool * YesNo,char ask[]) {
    char str[5];

    printf("%s ",ask);
    
#ifdef _WIN32
    fseek(stdin,0,SEEK_END);
#endif

    char * stdinError = fgets(str, 5, stdin);
    if (stdinError == NULL) {
        AbortMsg("Failed to read input!");
        return 2;
    }
    printf("\n");
    if (str[strlen(str)-1] != '\n') {
        PurgeStdin();
        return 1;
    }
    if (str[0] == '\n') {
        *YesNo = true;
        return 0;
    }
    str[strlen(str)-1] = '\0'; // remove '\n' at the end
    if (strcmp(str,"Yes") == 0 || strcmp(str,"yes") == 0 ||  strcmp(str,"y") == 0 || strcmp(str,"Y") == 0) {
        *YesNo =true;
        return 0;
    }
    if (strcmp(str,"No") == 0 || strcmp(str,"no") == 0 || strcmp(str,"n") == 0 || strcmp(str,"N") == 0) {
        *YesNo = false;
        return 0;
    }

    return 3;
}

/*
 * 0 ok / back
 * 1 enter
 * 2 moved
 * 3 loop
 */
int PromptCursor(Point * cursor,SizeMatrix size) {
    printf("\n[(Arrow Keys) to move, (Enter) to Kill / Revive, (9) to quit] ");
    char c = ReadChar();
    printf("\n");
    if (c == '9') {
        return 0;
    }

#ifdef _WIN32
    if (c == 13) {
        return 1;
    }
#else
    if (c == '\n') {
        return 1;
    }
#endif
    switch (c) {
        case ARROW_LEFT:
            if (size.x > cursor->x-1 && cursor->x-1 >= 0) {
                cursor->x-=1;
            }
            return 2;
            break;
        case ARROW_RIGHT:
            if (size.x > cursor->x+1 && cursor->x+1 >= 0) {
                cursor->x+=1;
            }
            return 2;
            break;
        case ARROW_UP:
            if (size.y > cursor->y-1 && cursor->y-1 >= 0) {
                cursor->y-=1;
            }
            return 2;
            break;
        case ARROW_DOWN:
            if (size.y > cursor->y+1 && cursor->y+1 >= 0) {
                cursor->y+=1;
            }
            return 2;
            break;
    }

    return 3;
}