#include <stdbool.h>

#define SAVE_FOLDER saves // folder name
#define FILE_FORMAT csv // .csv files
#define FILE_NAME_LENGTH 128

#ifndef FILE_HANDLER
#define FILE_HANDLER

typedef struct LoadedFileProperties {
    char fileName[FILE_NAME_LENGTH];
    bool didUserSave;
}LoadedFileProperties;

#endif /* FILE_HANDLER */

int InitSaveFolder();
bool FileNameHasBadChar(char str[]);