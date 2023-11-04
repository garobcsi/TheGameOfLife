#include <string.h>
#include <stdio.h>
#include "../util/Stringify.h"
#include "../util/Utils.h"
#include "FileHandler.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <errno.h>
#include <stdio_ext.h>
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