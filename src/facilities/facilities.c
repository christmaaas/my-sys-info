#include "facilities.h"

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

char* get_file(const char* filename) 
{
    FILE* file_ptr = fopen(filename, "r");

    if (file_ptr == NULL) 
    {
        perror("Error to open file in \"facilities.c\" : get_file()");
        return NULL;
    }

    fseek(file_ptr, 0, SEEK_END);
    size_t file_size = ftell(file_ptr);
    rewind(file_ptr);

    char* buffer = (char*)malloc(file_size + 1);

    size_t result = fread(buffer, 1, file_size, file_ptr);

    buffer[file_size] = '\0'; 

    fclose(file_ptr);

    return buffer;
}
