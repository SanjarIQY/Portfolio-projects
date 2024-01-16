#include "../h/main.h"

int MAX_BUFFER_SIZE = 48000;

void my_free(char* maze, int* arr, int* check_ind)
{
    if (maze != NULL)
    {
        free(maze);
    }
    if (arr != NULL)
    {
        free(arr);
    }
    if (check_ind != NULL)
    {
        free(check_ind);
    }
}

int my_mouse(char* file_name) {
    char* maze = read_whole_maze(file_name);
    int* arr = NULL;
    int* check_ind = NULL;
    
    if (maze != NULL) {
        if (check_for_file_name(file_name) == 1) {
            arr = read_first_line(maze);
            check_ind = check_col_line(maze);
        }
    }
    
    if (maze == NULL || arr == NULL || check_ind == NULL || check_ind[0] != arr[0] || check_ind[1] != arr[1] || check_amount_en_qu(maze) != 1) {
        my_free(maze, arr, check_ind);
        return 1;
    }

    if (s_maze(maze, arr) == 1)
    {
        my_free(maze, arr, check_ind);
        return 1;
    }
    my_free(maze, arr, check_ind);
    return 0;
}

int main(int argc, char** argv)
{
    if (argc == 1 || my_mouse(argv[1]) == 1)
    {
        map_error();
        return 1;
    }
    return 0 ;
}