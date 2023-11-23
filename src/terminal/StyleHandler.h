#ifndef STYLE_HANDLER_H
#define STYLE_HANDLER_H

//Cursor
void MoveCursorUp(int steps);

//Erase
void EraseInLine();

//Reset
void AnsiResetAll ();

//ForeColor
void AnsiColorBlack();
void AnsiColorRed();
void AnsiColorGreen();
void AnsiColorYellow();
void AnsiColorBlue();
void AnsiColorMagenta();
void AnsiColorCyan();
void AnsiColorWhite();

//Background
void AnsiBackgroundBlack();
void AnsiBackgroundRed();
void AnsiBackgroundGreen();
void AnsiBackgroundYellow();
void AnsiBackgroundBlue();
void AnsiBackgroundMagenta();
void AnsiBackgroundCyan();
void AnsiBackgroundWhite();

//Style
void StyleBold();
void StyleItalic();
void StyleUnderline();

#endif