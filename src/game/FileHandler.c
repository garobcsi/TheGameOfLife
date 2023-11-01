#include "../util/Stringify.h"
#include "../util/Utils.h"
#include "FileHandler.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/stat.h>
#include <errno.h>
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