#include "../h/my_string_lib.h"

int my_strcmp(char* str1, char* str2)
{
    for (; *str1 || *str2; str1++, str2++)
    {
        if (*str1 != *str2)
        {
            return ((*str1) - (*str2));
        }
    }
    return 0;
}

int my_strlen(char* str)
{
    int size = 0;
    while (str[size] != '\0')
    {
        size++;
    }
    return size;
}

char* my_scanf()
{
    char* ret_val = malloc(sizeof(char) * 20);
    int ind = 0;
    char letter;
    while (read(0, &letter, 1))
    {
        if (letter == '\n')
        {
            ret_val[ind] = '\0';
            return ret_val;
        }
        ret_val[ind] = letter;
        ind++;
    }
    return 0;
}

void fill_with_nol(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = 0;
    }
}

int* length_array_elements(char* string, char letter)
{
    int number_of_str = 1;
    for (int i = 0; i < my_strlen(string); i++)
    {
        if (string[i] == letter)
        {
            number_of_str++;
        }
    }
    int* ret_val = calloc(sizeof(int), (number_of_str + 1));
    int ind = 0;
    for (int i = 0; i < my_strlen(string); i++)
    {
        if (string[i] != letter)
        {
            ret_val[ind]++;
        }
        else
        {
            ind++;
        }
    }
    return ret_val;
}

char** split(char* input, char letter)
{
    int number_of_str = 1;
    for (int i = 0; i < my_strlen(input); i++)
    {
        if (input[i] == letter)
        {
            number_of_str++;
        }
    }

    char** ret_val = (char**)malloc(sizeof(char*) * (number_of_str + 1));
    int* length_of_elenments = length_array_elements(input, letter);
    int ind = 0;
    ret_val[ind] = malloc(sizeof(char) * length_of_elenments[ind] + 1);
    fill_with_null(ret_val[ind], length_of_elenments[ind] + 1);
    int string_ind = 0;

    for (int i = 0; i < my_strlen(input); i++)
    {
        if (input[i] != letter)
        {
            ret_val[ind][string_ind++] = input[i];
        }
        else
        {
            ind++;
            ret_val[ind] = malloc(sizeof(char) * (length_of_elenments[ind] + 1));
            fill_with_null(ret_val[ind], (length_of_elenments[ind] + 1));
            string_ind = 0;
        }
    }
    ret_val[++ind] = NULL;
    free(length_of_elenments);
    return ret_val;
}

char* my_strcpy(char* dst, char* src)
{
    for (; *src; dst++, src++)
    {
        *dst = *src;
    }
    return dst;
}

char* my_strncpy(char* dst, char* src, int over)
{
    for (int i = 0; i < over; i++)
    {
        dst[i] = src[i];
    }
    return dst;
}

int power(int num, int pw)
{
    int ret = 1;
    while (pw > 0)
    {
        ret *= num;
        pw--;
    }
    return ret;
}

int char_to_dec(char* str)
{
    int num = 0;
    int i = 0;
    int ind = power(10, my_strlen(str)) / 10;
    while (str[i])
    {
        num += (str[i] - 48) * ind;
        i++;
        ind /= 10;
    }
    return num;
}

void fill_with_null(char* str, int size)
{
    for (int i = 0; i < size; i++)
    {
        str[i] = '\0';
    }
}

char* dec_to_char(int num)
{
    int num2 = num;
    int length = 0;
    while (num2 > 0)
    {
        length++;
        num2 /= 10;
    }
    char* ret_val = malloc(sizeof(char) * length + 1);
    fill_with_null(ret_val, (length + 1));
    while (num > 0)
    {
        ret_val[length - 1] = (num % 10) + 48;
        length--;
        num /= 10;
    }
    return ret_val;
}

void split_gaps(char* str)
{
    int i = 0;
    while (str[i] == ' ')
    {
        for (int j = i; j < str[j]; j++)
        {
            str[j] = str[j + 1];
        }
        i = 0;
    }
    for (; str[i]; i++)
    {
        if (str[i] == ' ' && str[i + 1] == ' ')
        {
            for (int j = i; str[j]; j++)
            {
                str[j] = str[j + 1];
            }
            i = 0;
        }
    }
    if (str[my_strlen(str) - 1] == ' ')
        str[my_strlen(str) - 1] = '\0';
    else
        str[my_strlen(str)] = '\0';
}