#include <stdbool.h>
#include "GameLogic.h"

int InitSaveFolder();
bool FileNameHasBadChar(char str[]);
bool DoesFileExist(char * str);
int SaveMatrixToFile(Matrix * matrix,char * str);