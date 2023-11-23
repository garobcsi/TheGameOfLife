#ifndef FILE_HANDLER_STRUCT_H
#define FILE_HANDLER_STRUCT_H

#define SAVE_FOLDER saves // folder name
#define FILE_FORMAT csv // .csv files
#define FILE_NAME_LENGTH 128

#include <stdbool.h>

typedef struct GameFileProperties {
    char name[FILE_NAME_LENGTH];
    bool didUserSave;
}GameFileProperties;

typedef struct GameSaveFiles {
    char ** data;
    int count;
} GameSaveFiles;

#endif