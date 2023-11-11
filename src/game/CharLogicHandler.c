#include <string.h>
#include "../util/Utils.h"
#include "../../debugmalloc.h"

char * CpyStr(char * str) {
    char * tmp = (char *) malloc(sizeof(char)*strlen(str)+1);
    if (tmp == NULL) {
        AbortMsg("Memory allocation failed!");
        return NULL;
    }
    strcpy(tmp,str);
    return tmp;
}