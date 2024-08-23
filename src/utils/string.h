#ifndef _STRING_UTILS_H
#define _STRING_UTILS_H

char** strsplit(const char* str, const char* delim, int* num_tokens);
char* strduplicate(const char *str);
char* strconcat(const char* str1, const char* str2);

#endif /* _STRING_UTILS_H */