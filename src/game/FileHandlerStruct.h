#include <stdbool.h>

#define SAVE_FOLDER saves // folder name
#define FILE_FORMAT csv // .csv files
#define FILE_NAME_LENGTH 128

#ifndef FILE_HANDLER_STRUCT
#define FILE_HANDLER_STRUCT

typedef struct GameFileProperties {
    char name[FILE_NAME_LENGTH];
    bool didUserSave;
}GameFileProperties;

#endif /* FILE_HANDLER_STRUCT */