#include "string_utils.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* strduplicate(const char *str) 
{
    size_t len = strlen(str) + 1;

    char* dup = (char*)malloc(len);

    if (dup) 
        memcpy(dup, str, len);

    return dup;
}

char** strsplit(const char* str, const char* delim, int* num_tokens) {
    char* copy = strduplicate(str); 
    char** tokens = NULL;

    int count = 0;

    char* token = strstr(copy, delim);
    while (token) 
    {
        *token = '\0'; 
        tokens = (char**)realloc(tokens, (count + 1) * sizeof(char*));
        tokens[count++] = strduplicate(copy);

        copy = token + strlen(delim); 
        token = strstr(copy, delim);
    }

    tokens = (char**)realloc(tokens, (count + 1) * sizeof(char*));
    tokens[count++] = strduplicate(copy);

    *num_tokens = count;

    return tokens;
}

char* strconcat(const char* str1, const char* str2) 
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    char* result = (char*)malloc(len1 + len2 + 1); 
    
    strcpy(result, str1);
    strcat(result, str2);

    return result;
}