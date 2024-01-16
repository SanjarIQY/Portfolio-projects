#ifndef MY_STRING_LIB_H
#define MY_STRING_LIB_H
int my_strlen(char* str);
int my_strcmp(char* str1, char* str2);
char* my_strcpy(char* dst, char* src);
char* my_strncpy(char* dst, char* src, int over);
int power(int num, int pw);
int  char_to_dec(char* str);
char* dec_to_char(int num);
void fill_with_null(char* string, int size);
void split_gaps(char* str);
char** split(char* input, char letter);
char* my_scanf();
int* length_array_elements(char* string, char letter);
void fill_with_nol(int *arr, int size);
#endif