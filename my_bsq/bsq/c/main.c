#include "../h/main.h"

void read_from_file(char* map)
{
    struct stat fs;
    stat(map, &fs);
    if(fs.st_size == 0)
    {
        write(2, "map doesn't exist\n", 18);
        return;
    }
    else
    {
        int fd = open(map, O_RDONLY);
        char* map = calloc(sizeof(char), (fs.st_size + 1));
        read(fd, map, fs.st_size);
        close(fd);
        char** str2 = split(map,'\n');
        int i = 0;
        int** arr = (int**)calloc(sizeof(int*), (char_to_dec(str2[0]) + 1));
        while(i < (char_to_dec(str2[0])))
        {
            arr[i] = calloc(sizeof(int), my_strlen(str2[1]));
            map_to_digit(arr[i], str2[i + 1]);
            i++;
        }
        modify_arr(arr, my_strlen(str2[1]));
        matching_square(arr,my_strlen(str2[1]));
        free_array(str2);
        free(map);
        free_int_arr(arr);
    }
}

int main(int argc, char** argv)
{
    if(argc == 1){
        printf("select the file\n");
        return 1;
    }
    read_from_file(argv[1]);
    return 0;
}