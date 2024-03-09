#include "facilities.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

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

char* get_file_content(const char* filename) 
{
    FILE* file_ptr = NULL;

    if ((file_ptr = fopen(filename, "r")) == NULL) 
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

int get_count_of_files_name(const char* path, const char* name)
{
    DIR* dir;
    struct dirent* entry;
    int count = 0;

    dir = opendir(path);
    if (dir == NULL) 
    {
        perror("Error to open directory in \"facilities.c\" : get_count_of_files()");
        return -1;
    }

    while ((entry = readdir(dir)) != NULL) 
    {
        if (strstr(entry->d_name, name) != NULL) 
            count++;
    }

    closedir(dir);

    return count;
}
