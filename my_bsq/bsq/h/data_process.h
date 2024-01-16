#ifndef BSQ_H_DATA_PROCESS_H_
#define BSQ_H_DATA_PROCESS_H_

#include <stdlib.h>

#include "./my_string_lib.h"
#include "./structures.h"

int find_the_min(int p1, int p2, int p3);
void free_array(char** str);
void free_int_arr(int** arr);
void free_list(b_block* head);
void modify_arr(int** arr, int length_line);
void inner_loop(int** arr, int length_line, int i);
void add_list(b_block** header, char* line, int line_length);

#endif