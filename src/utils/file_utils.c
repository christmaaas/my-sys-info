#include "file_utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

char* get_file(const char* filename) 
{
    FILE* file_ptr = NULL;
    if ((file_ptr = fopen(filename, "r")) == NULL) 
    {
        perror("Error to open file in \"file_utils.c\" : get_file()");
        return NULL;
    }

    fseek(file_ptr, 0, SEEK_END);
    size_t file_size = ftell(file_ptr);
    rewind(file_ptr);

    char* buffer = (char*)malloc(file_size + 1);

    fread(buffer, sizeof(char), file_size, file_ptr);

    CUT_STRING_BY_LENGTH(buffer); 

    fclose(file_ptr);

    return buffer;
}

int get_file_int(const char* filename) 
{
    char* file_content = get_file(filename);

    int file_content_int = atoi(file_content);

    free(file_content);

    return file_content_int;
}

int get_count_of_files_name(const char* path, const char* name)
{
    DIR* dir = opendir(path);
    if (dir == NULL) 
    {
        perror("Error to open directory in \"file_utils.c\" : get_count_of_files_name()");
        return -1;
    }
    int count = 0;
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) 
    {
        if (strstr(entry->d_name, name) != NULL) 
            count++;
    }
    closedir(dir);

    return count;
}

int get_count_of_files(const char* path)
{
    DIR* dir = opendir(path);
    if (dir == NULL) 
    {
        perror("Error to open directory in \"file_utils.c\" : get_count_of_files()");
        return -1;
    }
    int count = 0;
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        count++;
    } 
    closedir(dir);

    return count;
}
