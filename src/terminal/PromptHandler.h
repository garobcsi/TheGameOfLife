#ifndef PROMPT_HANDLER_H
#define PROMPT_HANDLER_H

char ReadChar();
int PromptMainMenu();
int PromptFileName(char * str);
SizeMatrix PromptMatrixSize(Game * game);
int PromptFileLoad(int * select,GameSaveFiles * files,Game * game);
int PromptBack();
int PromptGameMenu();
int PromptYesNo(bool * YesNo,char ask[]);
int PromptCursor(Point * cursor,SizeMatrix size);

#endif