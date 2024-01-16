#ifndef BSQ_H_STRUCTURES_H_
#define BSQ_H_STRUCTURES_H_

typedef struct blocks
{
    char* line;
    struct blocks* next;
} b_block;

typedef struct square_d
{
    int* line_arr;
    int* index_arr;
    int line_max;
    int index_max;
    int max_num;
} square_data;

#endif