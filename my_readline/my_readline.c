#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int READLINE_READ_SIZE = 6;
char* storage;

typedef struct list
{
    int size;
    int count;
    char* text;
} one_line;

void copy(char* dest, char* source)
{
    int i = 0;
    while(source[i] != '\0')
    {
        dest[i] = source[i];
        i++;
    }
}

int my_strlen(char* string)
{
    int i = 0;
    while(string[i] != '\0')
        i++;
    return i;
}

void fill_with_null(char* string, int length)
{
    int i = 0;
    while(i <= length)
    {
        string[i] = '\0';
        i++;
    }
}

char* add_some_memory(char* text, int size)
{
    char* temp = malloc(sizeof(char) * (size + 1 + READLINE_READ_SIZE));
    fill_with_null(temp, (size + READLINE_READ_SIZE));
    copy(temp, text);
    free(text);
    return temp;
}

void to_storage(char* after_new_line)
{
    fill_with_null(storage, READLINE_READ_SIZE);
    int i = 0;
    while(after_new_line[i] != '\0')
    {
        storage[i] = after_new_line[i];
        i++;
    }
    storage[i] = '\0';
}

void init_string(char* string)
{
    if(string)
        free(string);

    string = malloc(sizeof(char) * READLINE_READ_SIZE + 1);
    fill_with_null(string, READLINE_READ_SIZE);
}

void init_my_readline()
{
    if(storage)
        free(storage);

    storage = malloc(sizeof(char) * READLINE_READ_SIZE + 1);
    fill_with_null(storage, READLINE_READ_SIZE);  
    // storage[READLINE_READ_SIZE] = '\0';      
}

int check_for_new_line(one_line* answer, char* temp)
{   
    int length = my_strlen(temp);
    int i = 0;
    while(i < length)
    {
        if(temp[i] == '\n')
        {
            to_storage(&temp[i + 1]);
            return 1;
        }

        if(answer->size == (READLINE_READ_SIZE) * answer->count)
        {
            answer->count++;
            answer->text = add_some_memory(answer->text, answer->size);
        }
        answer->text[answer->size++] = temp[i];
        i++;
    }
    return 0;
}

char* my_readline(int fd)
{
    if(fd != 3 && fd != 0){
        return NULL;
    }
    one_line answer;
    answer.count = 1;
    answer.size = 0;
    answer.text = malloc(sizeof(char) * (READLINE_READ_SIZE + 1));
    fill_with_null(answer.text, READLINE_READ_SIZE);
    char* temp = NULL;
    if(storage)
    {
        temp = malloc(sizeof(char) * (READLINE_READ_SIZE + 1));
        fill_with_null(temp, READLINE_READ_SIZE);
        copy(temp, storage);

        if(check_for_new_line(&answer, temp) == 1)
        {
            free(temp);
            return answer.text;
        }
    }
    fill_with_null(temp, READLINE_READ_SIZE);
    while(read(fd, temp, READLINE_READ_SIZE))
    {
        if(check_for_new_line(&answer, temp) == 1)
        {
            free(temp);
            return answer.text;
        }
       fill_with_null(temp, READLINE_READ_SIZE);
    }
    if(answer.text[0]){
        free(temp);
        return answer.text;
    }
    free(temp);
    free(answer.text);
    return NULL;
}

int main(int argc, char** argv) {
    
    char *string = NULL;
    init_my_readline();

    int fd = 0;

    while ((string = my_readline(fd)) != NULL) {
        printf("%s\n", string);
        free(string);
    }
    close(fd);

    return 0;
}