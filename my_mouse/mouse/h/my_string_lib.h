#ifndef MY_STRING_LIB_H_
#define MY_STRING_LIB_H_

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int my_strlen(char* str);
int char_to_dec(char* str);
int power(int num, int pw);
int is_digit(char character);
int my_strcmp(char* str1, char* str2);
int number_of_string(char* string, char letter);
int* length_array_elements(char* string, char letter);
int* inner_work(int number_of_str, char* string,char letter);
void split_gaps(char* str);
void free_str_arr(char** str);
void fill_with_nol(int* arr, int size);
void fill_with_null(char* string, int size);
void fill_array(char* input, char letter, char** ret_val, int* ind, int* length_of_elenments);
char* my_strcpy(char* dst, char* src);
char* my_strncpy(char* dst, char* src, int over);
char* dec_to_char(int num);
char* my_scanf();
char** split(char* input, char letter);


#endif