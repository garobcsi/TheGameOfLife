#include "../../debugmalloc.h"

//Cursor
void MoveCursorUp(int steps) {
    for (int i = 0; i < steps; ++i) {
        printf("\x1b[1A");

    }
}

//Erase
void EraseInLine() {
    printf("\x1b[K");
}

//Reset
void AnsiResetAll () {
    printf("\x1b[0m");
}

//ForeColor
void AnsiColorBlack() {
    printf("\x1b[30m");
}
void AnsiColorRed() {
    printf("\x1b[31m");
}
void AnsiColorGreen() {
    printf("\x1b[32m");
}
void AnsiColorYellow() {
    printf("\x1b[33m");
}
void AnsiColorBlue() {
    printf("\x1b[34m");
}
void AnsiColorMagenta() {
    printf("\x1b[35m");
}
void AnsiColorCyan() {
    printf("\x1b[36m");
}
void AnsiColorWhite() {
    printf("\x1b[37m");
}

//Background
void AnsiBackgroundBlack() {
    printf("\x1b[40m");
}
void AnsiBackgroundRed() {
    printf("\x1b[41m");
}
void AnsiBackgroundGreen() {
    printf("\x1b[42m");
}
void AnsiBackgroundYellow() {
    printf("\x1b[43m");
}
void AnsiBackgroundBlue() {
    printf("\x1b[44m");
}
void AnsiBackgroundMagenta() {
    printf("\x1b[45m");
}
void AnsiBackgroundCyan() {
    printf("\x1b[46m");
}
void AnsiBackgroundWhite() {
    printf("\x1b[47m");
}

//Style
void StyleBold() {
    printf("\x1b[1m");
}
void StyleItalic() {
    printf("\x1b[3m");
}
void StyleUnderline() {
    printf("\x1b[4m");
}