#include <string.h>
#include "../../debugmalloc.h"

char * CpyStr(char * str) {
    char * tmp = (char *) malloc(sizeof(char)*strlen(str)+1);
    if (tmp == NULL) return NULL;
    strcpy(tmp,str);
    return tmp;
}