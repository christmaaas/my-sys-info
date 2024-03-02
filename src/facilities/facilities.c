#include "facilities.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** strsplit(const char* str, const char* delim, int* num_tokens) {
    char* copy = strdup(str); 
    char** tokens = NULL;

    int count = 0;

    char* token = strtok(copy, delim);
    while (token) 
    {
        tokens = realloc(tokens, (count + 1) * sizeof(char*));

        tokens[count++] = strdup(token);

        token = strtok(NULL, delim);
    }

    *num_tokens = count;

    free(copy);

    return tokens;
}
