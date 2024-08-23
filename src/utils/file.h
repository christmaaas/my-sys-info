#ifndef _FILE_UTILS_H
#define _FILE_UTILS_H

#define FILE_BUFFER_SIZE  256
#define MAX_FILE_PATH_LEN 1024

#define CUT_STRING_BY_LENGTH(str)  \
        if ((str))                 \
            (str)[strlen(str) - 1] = '\0';

char* get_file(const char* filename);
int get_file_int(const char* filename);
int get_count_of_files_name(const char* path, const char* name);
int get_count_of_files(const char* path);

#endif /* _FILE_UTILS_H */