#include <stdio.h>

//Reset
void ResetAll () {
    printf("\x1b[0m");
}

//ForeColor
void ColorBlack() {
    printf("\x1b[30m");
}
void ColorRed() {
    printf("\x1b[31m");
}
void ColorGreen() {
    printf("\x1b[32m");
}
void ColorYellow() {
    printf("\x1b[33m");
}
void ColorBlue() {
    printf("\x1b[34m");
}
void ColorMagenta() {
    printf("\x1b[35m");
}
void ColorCyan() {
    printf("\x1b[36m");
}
void ColorWhite() {
    printf("\x1b[37m");
}

//Backgorund
void BackgroundBlack() {
    printf("\x1b[40m");
}
void BackgroundRed() {
    printf("\x1b[41m");
}
void BackgorundGreen() {
    printf("\x1b[42m");
}
void BackgorundYellow() {
    printf("\x1b[43m");
}
void BackgorundBlue() {
    printf("\x1b[44m");
}
void BackgorundMagenta() {
    printf("\x1b[45m");
}
void BackgorundCyan() {
    printf("\x1b[46m");
}
void BackgorundWhite() {
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