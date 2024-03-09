#ifndef _FACILITIES_H
#define _FACILITIES_H

// здесь будет что-то типа utils
// т.е. функции для чтения файлов, парсинга из них инфы и т.д.

#define FILE_BUFFER_SIZE    256
#define MAX_FILE_PATH_LEN   1024

char** strsplit(const char* str, const char* delim, int* num_tokens);
char* strduplicate(const char *str);
char* strconcat(const char* str1, const char* str2);
char* get_file_content(const char* filename);
int get_count_of_files_name(const char* path, const char* name);


#endif /* _FACILITIES_H */