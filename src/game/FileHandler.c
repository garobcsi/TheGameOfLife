#include <string.h>
#include <stdio.h>
#include "FileHandler.h"
#include "CharLogicHandler.h"
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
#include <dirent.h>
#endif

char * MakePath(char * str) {
    char * folderName = STRINGIFY_VALUE(SAVE_FOLDER);
    char * fileExt = STRINGIFY_VALUE(FILE_FORMAT);
    char * f = (char*)malloc(sizeof(char) * (strlen(folderName) + strlen(str) + strlen(fileExt) +3));
    if (f == NULL) {
        free(f);
        return NULL;
    }
    f[0]='\0';
    strcat(f,folderName);
    strcat(f,"/");
    strcat(f,str);
    strcat(f,".");
    strcat(f,fileExt);
    return f;
}

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
    char * f = MakePath(str);
#ifdef _WIN32
    tmp = access(f, 0) == 0;
#else
    tmp = access(f, F_OK) == 0;
#endif
    free(f);
    return tmp;
}

/*
 * 0 ok
 * 1 failed to open file
 * 2 failed to allocate memory
 * */
int SaveMatrixToFile(Matrix * matrix,char * str) {
    FILE *file;
    char * path = MakePath(str);
    if (path == NULL) {
        return 2;
    }
    file = fopen(path, "w");
    if (file == NULL) {
        AbortMsg("Failed to create file!");
        return 1;
    }
    fprintf(file, "%d;%d\n",(int)matrix->size.x,(int)matrix->size.y);
    for (int i = 0; i < (int)matrix->size.y; ++i) {
        fprintf(file,"%d",matrix->data[0][i]);
        for (int j = 1; j < (int)matrix->size.x; ++j) {
            fprintf(file,";%d",matrix->data[j][i]);
        }
        fprintf(file,"\n");
    }

    fclose(file);
    free(path);
    return 0;
}

/*
 * 0 ok
 * 1 catastrophic failure
 * */
int GetSaveFiles(GameSaveFiles ** files) {
#ifdef _WIN32
    WIN32_FIND_DATA findFileData;
    HANDLE hFind = INVALID_HANDLE_VALUE;
    DWORD error = 0;
#else

    DIR * dir;
    struct dirent * entry;
#endif
    *files = (GameSaveFiles *)malloc(sizeof(GameSaveFiles));
    if (*files == NULL) {
        free((*files));
        return 1;
    }

    (*files)->count= 0;
    (*files)->data = NULL;

#ifdef _WIN32
    char path[MAX_PATH];
    snprintf(path, MAX_PATH, "%s\\*", STRINGIFY_VALUE(SAVE_FOLDER));

    hFind = FindFirstFile(path, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        free(*files);
        *files = NULL;
        return 1;
    }
#else
    dir = opendir(STRINGIFY_VALUE(SAVE_FOLDER));
    if (dir == NULL) {
        free((*files));
        *files = NULL;
        return 1;
    }
#endif

#ifdef _WIN32
    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
#else
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
#endif
            (*files)->data = (char**)realloc((*files)->data, sizeof(char*) * ((*files)->count + 1));
            if ((*files)->data == NULL) {
                for (size_t i = 0; i < (*files)->count; i++) {
                    if ((*files)->data[i] != NULL) free((*files)->data[i]);
                }
                free((*files)->data);
                free(*files);
                *files = NULL;
            #ifdef _WIN32
                FindClose(hFind);
            #else
                closedir(dir);
            #endif
                return 1;
            }

        #ifdef _WIN32
            (*files)->data[(*files)->count] = CpyStr(findFileData.cFileName);
        #else
            (*files)->data[(*files)->count] = CpyStr(entry->d_name);
        #endif
            if ((*files)->data[(*files)->count] == NULL) {
                for (size_t i = 0; i < (*files)->count; i++) {
                    if ((*files)->data[i] != NULL) free((*files)->data[i]);
                }
                free((*files)->data);
                free(*files);
                *files = NULL;
            #ifdef _WIN32
                FindClose(hFind);
            #else
                closedir(dir);
            #endif
                return 1;
            }
            (*files)->count++;
        }
#ifdef _WIN32 
    } while (FindNextFile(hFind, &findFileData) != 0);

    error = GetLastError();
    if (error != ERROR_NO_MORE_FILES) {
        for (int i = 0; i < (*files)->count; i++) {
            if ((*files)->data[i] != NULL) free((*files)->data[i]);
        }
        free((*files)->data);
        free(*files);
        *files = NULL;
        return 1;
    }
    FindClose(hFind);
#else
    }
    closedir(dir);
#endif

    return 0;

}

void DestroyStructSaveFiles(GameSaveFiles * files) {
    if (files != NULL) {
        for (size_t i = 0; i < files->count; i++) {
            if (files->data[i] != NULL) free(files->data[i]);
        }
        free(files->data);
        free(files);
    }
}