#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "my_string_lib.h"
#include "data_process.h"
#include "check_func.h"

int my_mouse(char* file_name);
void my_free(char* maze, int* arr, int* check_ind);

extern int MAX_BUFFER_SIZE;

#endif