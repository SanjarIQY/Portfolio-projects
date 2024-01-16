#ifndef BSQ_H_SEARCH_PROCESS_H_
#define BSQ_H_SEARCH_PROCESS_H_

#include <stdio.h>
#include <stdlib.h>

#include "./structures.h"
#include "./my_string_lib.h"
#include "./data_process.h"

void print_list(b_block* head);
void map_to_digit(int* dest, char* map);
int* finding_line(int index_max, int max_num);
int* finding_column(int line_max, int max_num);
int l_line_flag(square_data* map, int i);
int i_index_flag(square_data* map, int j);
int checking_ind(square_data* map, int j, int i);
void filling_with_xo(square_data* map, int ind, int length_line, int** arr, char* line);
square_data beg_matching(int** arr, int length_line);
void matching_square(int** arr, int length_line);

#endif