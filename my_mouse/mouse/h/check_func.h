#ifndef CHECK_FUNCSC
#define CHECK_FUNCSC

int check_amount_en_qu(char* maze);
int check_for_file_name(char* file_name);
int* check_col_line(char* map);
char identify_num(int digit);
void map_error();
void inside_the_loop(char* map,int* i, int* column, int* line);

#endif