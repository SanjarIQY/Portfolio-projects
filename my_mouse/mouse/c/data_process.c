#include "../h/main.h"

void print_maze(map_struct* current_map)
{
    for (int i = 0; i < current_map->col; i++)
    {
        for (int j = 0; j < current_map->line; j++)
        {
            printf("%d ", current_map->arr[i][j]);
        }
        printf("\n");
    }
}

int* result_maze(char* file_name, char** str_indexes)
{
    int* read_arr = calloc(5, sizeof(int));
    read_arr[0] = 0;
    read_arr[1] = 0;
    read_arr[2] = 0;
    read_arr[3] = 0;

    while (file_name[read_arr[0]] != '\n' && file_name[read_arr[0]] != '*' && file_name[read_arr[0]] != ' ')
    {
        if (is_digit(file_name[read_arr[0]]) == 0)
        {
            str_indexes[read_arr[1]][read_arr[2]++] = file_name[read_arr[0]];
        }
        else 
        {
            read_arr[3]++;
            read_arr[1]++;
            str_indexes[read_arr[1]] = calloc(sizeof(char), 10);
            read_arr[2] = 0;
        }
        read_arr[0]++;
    }

    return read_arr;
}

int* read_first_line(char* file_name)
{
    if (is_digit(file_name[0]) == 1)
    {
        return NULL;
    }

    char** str_indexes = calloc(sizeof(char*), 5);
    str_indexes[0] = calloc(sizeof(char), 10);
    
    int* result = result_maze(file_name, str_indexes);
    if(result[3] == 1)
    {
        int* col_line = calloc(sizeof(int), 3);
        col_line[0] = char_to_dec(str_indexes[0]);
        col_line[1] = char_to_dec(str_indexes[1]);
        free(result);
        free_str_arr(str_indexes);
        return col_line;
    }
    free(result);
    free_str_arr(str_indexes);
    return NULL;
}

void check_end(int* col_line, int flag, int i, int j)
{
    switch (flag) {
        case 1:
            col_line[0] = i;
            col_line[1] = j + 1;
            return;
        case 2: 
            col_line[0] = i;
            col_line[1] = j - 1;
            return;
        case 3: 
            col_line[0] = i + 1;
            col_line[1] = j;
            return;
    }
}

int* finding_end_quit(map_struct* current_map, int i, int j)
{
    int* col_line = calloc(sizeof(int), 3);
    if (current_map->arr[i][j + 1] == -2)
    {
        check_end(col_line, 1, i,j);
        return col_line;
    }
    else if (current_map->arr[i][j - 1] == -2)
    {
        check_end(col_line, 2, i,j);
        return col_line;
    }
    else if (current_map->arr[i + 1][j] == -2)
    {
        check_end(col_line, 3, i,j);
        return col_line;
    }
    free(col_line);
    return 0;
}

int finding_enter(map_struct* current_map, int i, int j)
{
    if (current_map->arr[i-1][j] == -1)
    {
        current_map->arr[i][j] = -3;
        return -1;
    }

    return 0;
}

void drawing_path(map_struct* current_map, int* indexes, int i, int j, int flag)
{
    switch (flag) {
        case 1:
            current_map->arr[i][j] = -3;
            indexes[0] = i - 1;
            indexes[1] = j;
            break;
        case 2:
            current_map->arr[i][j] = -3;
            indexes[0] = i;
            indexes[1] = j - 1;
            break;
        case 3:
            current_map->arr[i][j] = -3;
            indexes[0] = i;
            indexes[1] = j + 1;
            break;
        case 4: 
            current_map->arr[i][j] = -3;
            indexes[0] = i + 1;
            indexes[1] = j;
            break;
    }
}

 int* finding_path(map_struct* current_map, int i, int j)
{
    int current_value = current_map->arr[i][j];
    int* indexes = calloc(sizeof(int), 3);
    if (current_map->arr[i - 1][j] != 0 && current_map->arr[i - 1][j] == current_value - 1)
    {
        drawing_path(current_map, indexes, i, j, 1);
    }
    else if (current_map->arr[i][j - 1] != 0 && current_map->arr[i][j - 1] == current_value - 1)
    {
        drawing_path(current_map, indexes, i, j, 2);
    }
    else if (current_map->arr[i][j + 1] != 0 && current_map->arr[i][j + 1] == current_value - 1)
    {
        drawing_path(current_map, indexes, i, j, 3);
    }
    else if (current_map->arr[i + 1][j] != 0 && current_map->arr[i + 1][j] == current_value - 1)
    {
        drawing_path(current_map, indexes, i, j, 4);
    }
    return indexes;
}

 char* read_whole_maze(char* file_name)
{
    int map_fd = open(file_name, O_RDONLY);
    if (map_fd == -1) {
        close(map_fd);
        return NULL;
    }
    char temp ;
    char* whole_map = calloc(sizeof(char), MAX_BUFFER_SIZE);
    int map_ind = 0;
    while (read(map_fd, &temp,1))
    {
        whole_map[map_ind] = temp;
        map_ind++;
    }
    close(map_fd);

    int i = 0;
    while (whole_map[i])
    {
        if (whole_map[i] == '\n' && whole_map[i + 1] != '*' && whole_map[i + 2] != ' ')
        {
            break;
        }
        i++;
    }
    whole_map[i] = '\0';

    return whole_map;
}

 void matching_maze(int** arr, char letter, int ind, int j)
{
    if (letter == '*')
    {
        arr[ind][j] = 0;
    }
    else if (letter == ' ')
    {
        arr[ind][j] = 1;
    }
    else if (letter == '1')
    {
        arr[ind][j] = -1;
    }
    else if (letter == '2')
    {
        arr[ind][j] = -2;
    }
}

map_struct* convert_to_digital(char** maze, int* col_line)
{
    map_struct* current_maze = malloc(sizeof(map_struct));
    current_maze->arr = calloc((col_line[0]) + 1, sizeof(int*));
    int maze_ind = 0;
    current_maze->col = col_line[0];
    current_maze->line = col_line[1];

     for (int i = 1; i < col_line[0] + 1; i++)
    {
        current_maze->arr[maze_ind] = calloc(col_line[1], sizeof(int) + 1);
        for (int j = 0; j < col_line[1]; j++)
        {
            matching_maze(current_maze->arr,maze[i][j], maze_ind, j);
        }
        maze_ind++;
    }
    return current_maze;
}

void adding_value(map_struct* current_maze, int i, int j, int add_value)
{
    if (current_maze->arr[i - 1][j] == 1 && current_maze->arr[i - 1][j] != -1)
    {
        current_maze->arr[i - 1][j] = 1 + add_value;
    }
    if (current_maze->arr[i + 1][j] == 1)
    {
        current_maze->arr[i + 1][j] = 1 + add_value;
    }
    if (current_maze->arr[i][j - 1] == 1)
    {
        current_maze->arr[i][j - 1] = 1 + add_value;
    }
    if (current_maze->arr[i][j + 1] == 1)
    {
        current_maze->arr[i][j + 1] = 1 + add_value;
    }
}

 void converting_completed_map(map_struct* current_map)
{
    char* final_map = calloc((current_map->col * current_map->line) + (current_map->col + 1) + (my_strlen(current_map->first_line) + 1), sizeof(char));
    int ind = 0;
    my_strcpy(final_map, current_map->first_line);
    
    ind += my_strlen(final_map);
    final_map[ind] = '\n';
    ind++;
    int counter = 0;
    for (int i = 0; i < current_map->col; i++)
    {
        for (int j = 0; j < current_map->line; j++)
        {
            final_map[ind] = identify_num(current_map->arr[i][j]);
            if (final_map[ind] == 'o') counter++;
            ind++;
        }
        final_map[ind++] = '\n';
    }
    printf("%s", final_map);
    printf("%d STEPS\n", counter);
    free(final_map);
}

 void path(map_struct* current_map, int i, int j)
{
    int result = 0;
    int* col_line;
    while (result != -1)
    {
        col_line = finding_path(current_map,i, j);
        i = col_line[0];
        j = col_line[1];
        result = finding_enter(current_map, i, j);
        free(col_line);
    }
}

 void matching_path(map_struct* current_map, int* end_point)
{
    int i = 0;
    int j = 0;
    if (end_point[1] == current_map->line - 1)
    {
        i = end_point[0];
        j = current_map->line - 2;
    }
    else if (end_point[1] == 0)
    {
        i = end_point[0];
        j = 1;
    }
    else 
    {
        i = end_point[0] - 1;
        j = end_point[1];
    }
    path(current_map, i, j);
}

int* process_maze(map_struct* current_map, int* manipulate_struct, int* result) 
{
    for (int i = 1; i < current_map->col - 1; i++) {
        for (int j = 1; j < current_map->line - 1; j++) {
            if (manipulate_struct[0] == current_map->arr[i][j]) {
                result = finding_end_quit(current_map, i, j);
                if (result != 0) {
                    manipulate_struct[2] = -1;
                    break;
                }
                
                adding_value(current_map, i, j, manipulate_struct[0]);
            }
        }
        if (manipulate_struct[2] == -1) {
            manipulate_struct[1] = -1;
            break;
        }
    }
    manipulate_struct[0]++;
    return result;
}

int manipulating_maze(map_struct* current_map, int start_index)
 {
    if (current_map->arr[1][start_index] == 1) {
        current_map->arr[1][start_index] = 2;
        int* manipulate_struct = calloc(4, sizeof(int));
        manipulate_struct[0] = 2;
        manipulate_struct[1] = 0;
        manipulate_struct[2] = 0;
        int* result = 0;
        int counter = 0;
        while (manipulate_struct[1] != -1) {
            result = process_maze(current_map, manipulate_struct, result);
            if (counter > (current_map->col * current_map->line))
            {
                free(manipulate_struct);
                free(result);
                return 0;
            } 
            counter++;
        }
        matching_path(current_map, result);
        free(manipulate_struct);
        free(result);
        converting_completed_map(current_map);
        return 1;
    } else {
        return 0;
    }
}

 void my_free_struct(map_struct* current_map)
{
    free(current_map->first_line);
    for (int i = 0; i < current_map->col; i++)
    {
        free(current_map->arr[i]);
    }
    free(current_map->arr);
    free(current_map);
}

 int enter_index(int* arr, int line)
{
    int i = 0;
    while (i < line)
    {
        if (arr[i] == -1)
        {
            return i;
        }
        i++;
    }
    return 0;
}

int s_maze(char* maze, int* col_line)
{
    char** splited_maze = split(maze, '\n');    
    map_struct* digital_maze = convert_to_digital(splited_maze, col_line);
    digital_maze->first_line = calloc(sizeof(char), digital_maze->line + 1);
    my_strcpy(digital_maze->first_line, splited_maze[0]);
    int index = enter_index(digital_maze->arr[0], col_line[1]);
    if (manipulating_maze(digital_maze, index) == 0){
        free_str_arr(splited_maze);
        my_free_struct(digital_maze);
        return 1;
    }
    free_str_arr(splited_maze);
    my_free_struct(digital_maze);
    return 0;
}