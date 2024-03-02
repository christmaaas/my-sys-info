#ifndef _FACILITIES_H
#define _FACILITIES_H

// здесь будет что-то типа utils
// т.е. функции для чтения файлов, парсинга из них инфы и т.д.

#define FILE_BUFFER_SIZE 256

char** strsplit(const char* str, const char* delim, int* num_tokens);


#endif /* _FACILITIES_H */