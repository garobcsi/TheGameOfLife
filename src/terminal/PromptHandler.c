#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "../util/Utils.h"
#include "../game/GameLogic.h"
#include "../game/FileHandler.h"
#include "../../debugmalloc.h"

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
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