#ifndef DATA_PROCESS_F
#define DATA_PROCESS_F

typedef struct map_struct
{
    int col;
    int line;
    int** arr;
    char* first_line;
} map_struct;

int enter_index(int* arr, int line);
int s_maze(char* maze, int* col_line);
int finding_enter(map_struct* current_map, int i, int j);
int manipulating_maze(map_struct* current_map, int start_index);
int* read_first_line(char* file_name);
int* result_maze(char* file_name, char** str_indexes);
int* finding_path(map_struct* current_map, int i, int j);
int* finding_end_quit(map_struct* current_map, int i, int j);
int* process_maze(map_struct* current_map, int* manipulate_struct, int* result);
char* read_whole_maze(char* file_name);
void my_free_struct(map_struct* current_map);
void path(map_struct* current_map, int i, int j);
void check_end(int* col_line, int flag, int i, int j);
void converting_completed_map(map_struct* current_map);
void matching_maze(int** arr, char letter, int ind, int j);
void matching_path(map_struct* current_map, int* end_point);
void adding_value(map_struct* current_maze, int i, int j, int add_value);
void drawing_path(map_struct* current_map, int* indexes, int i, int j, int flag);
map_struct* convert_to_digital(char** maze, int* col_line);


#endif