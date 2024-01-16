#ifndef STRING_LIB
#define STRING_LIB
int my_strlen(char* string);
void my_strcpy(char* dest, char* source);
void my_strncpy(char* dest, char* source, int size);
void fill_with_null(char* string, int size);
void split_gaps(char* task);
int power(int num, int pw);
int char_to_dec(char* str);
int my_strcmp(char* str1, char* str2);
#endif