#include "../../debugmalloc.h"
#include "../util/Utils.h"

char * CpyStr(char * str) {
    char * tmp = (char *) malloc(sizeof(char)*(strlen(str)+1));
    if (tmp == NULL) {
        free(tmp);
        AbortMsg("Memory allocation failed!");
        return NULL;
    }
    strcpy(tmp,str);
    return tmp;
}