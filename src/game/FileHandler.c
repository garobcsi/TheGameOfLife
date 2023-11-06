#include <string.h>
#include <stdio.h>
#include "FileHandler.h"
#include "../util/Stringify.h"
#include "../util/Utils.h"
#include "../../debugmalloc.h"

#ifdef _WIN32
#include <windows.h>
#include <io.h>
#else
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#endif

int InitSaveFolder() {
    #ifdef _WIN32
        if (!CreateDirectory(STRINGIFY_VALUE(SAVE_FOLDER), NULL)) {
            if (GetLastError() != ERROR_ALREADY_EXISTS) {
                AbortMsg("Failed to create folder!");
                return 1;
            }
        }
    #else
        if (mkdir(STRINGIFY_VALUE(SAVE_FOLDER), 0755) != 0) {
            if (errno != EEXIST) {
                AbortMsg("Failed to create folder!");
                return 1;
            }
        }
    #endif

    return 0;
}

bool FileNameHasBadChar(char str[]) {
    const char* badChars = "<>:\"/\\|?*";

    for (size_t i = 0; str[i] != '\0'; i++) {
        if (strchr(badChars, str[i]) != NULL) {
            return true;
        }
    }

    return false;
}

bool DoesFileExist(char * str) {
    bool tmp = false;
    char * folderName = STRINGIFY_VALUE(SAVE_FOLDER);
    char * fileExt = STRINGIFY_VALUE(FILE_FORMAT);
    char * f = (char*)malloc(sizeof(char) * strlen(folderName) * strlen(str) * strlen(fileExt) +3);
    f[0]='\0';
    strcat(f,folderName);
    strcat(f,"/");
    strcat(f,str);
    strcat(f,".");
    strcat(f,fileExt);
#ifdef _WIN32
    tmp = access(f, 0) == 0;
#else
    tmp = access(f, F_OK) == 0;
#endif
    free(f);
    return tmp;
}