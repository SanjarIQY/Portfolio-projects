#include "../h/main.h"

void map_error() 
{
    char* ERROR = calloc(sizeof(char), 10);
    my_strcpy(ERROR, "MAP ERROR");
    write(2, ERROR, 9);
    free(ERROR);
}

char identify_num(int digit) {
    switch (digit) {
        case 0:
            return '*';
        case -3:
            return 'o';
        case -1:
            return '1';
        case -2:
            return '2';
        default:
            return ' ';
    }
}

void inside_the_loop(char* map,int* i, int* column, int* line)
{
    if ((map[*i] == '\n' && map[*i + 1] == '\n') || (map[*i] == '\n' && map[*i + 1] == ' ')){
            return;
        }
    if (map[*i] == '\n'){
        *line = 0;
        *column += 1;
    }
    else{
        *line += 1;
    }
    *i += 1;
}

int* check_col_line(char* map)
{
    int i = 0;
    int column = 0;
    int line = 0;
    int* indexes = calloc(sizeof(int), 3);
    
    while (map[i]){
        inside_the_loop(map, &i, &column, &line);
    }

     indexes[0] = column;
    indexes[1] = line;
    return indexes;
}

int check_amount_en_qu(char* maze){
    int first_counter = 0;
    int second_counter = 0;
    int n_flag = 0;
    for (int i = 0; maze[i]; i++){
        if (maze[i] == '\n'){
            n_flag = 1;
        }
        if (n_flag == 1 && maze[i] == '1'){
            first_counter++;
        }
        if (n_flag == 1 && maze[i] == '2'){
            second_counter++;
        }
    }

     if (second_counter != 1 || first_counter != 1){
        return 0;
    }
    return 1;
}

int check_for_file_name(char* file_name)
{
    int flag = 0;
    for (int i = 0; file_name[i]; i++)
    {
        if (file_name[i] == '.') flag = 1;
        if (flag == 1 && my_strcmp(&file_name[i],"map") == 0)
        {
            return 1;
        }
    }
    return 0;
}