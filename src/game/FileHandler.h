#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdbool.h>
#include "GameLogic.h"

int InitSaveFolder();
bool FileNameHasBadChar(char str[]);
bool DoesFileExist(char * str);
int SaveMatrixToFile(Matrix * matrix,char * str);
int GetSizeFromFile (SizeMatrix * size, GameSaveFiles * files,int select);
int LoadGameFromFile(Game * game,GameSaveFiles * files,int select);
int GetSaveFiles(GameSaveFiles ** files);
void DestroyStructSaveFiles(GameSaveFiles * files);

#endif