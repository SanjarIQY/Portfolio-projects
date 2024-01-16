#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>

int my_strlen(char* str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return i;
}

char* reversed_string(char* str, int flag)
{
    char* reversed_one = calloc(sizeof(char), my_strlen(str) + 2);
    int ind = 0;
    if (flag == 0)
    {
        ind++;
        reversed_one[0] = '-';
    }

    for (int i = my_strlen(str) - 1; i >= 0; i--)
    {
        reversed_one[ind++] = str[i];
    }
    free(str);
    reversed_one[ind] = '\0';
    return reversed_one;
}

char* my_atoi(int num, int flag)
{
    if (flag == 0)
    {
        num *= -1;
    }

    int copy_num = num;
    int count = 0;
    while (copy_num != 0)
    {
        count++;
        copy_num /= 10;
    }

    char* str_num = calloc(sizeof(char), count + 2);
    int ind = 0;

    while (num != 0)
    {
        str_num[ind++] = num % 10 + 48;
        num /= 10;
    }

    return reversed_string(str_num, flag);
}

char* x_option(long int num)
{
    long int copy_num = num;
    long int count = 0;
    while (copy_num != 0)
    {
        count++;
        copy_num /= 10;
    }

    char* ret_value = calloc(sizeof(char), count + 1);
    int ind = 0;
    while (num != 0)
    {
        int reminder = num % 16;
        if (reminder < 10)
        {
            ret_value[ind++] = reminder + '0';
        }
        else
        {
            ret_value[ind++] = reminder + 87;
        }
        num /= 16;
    }

    return reversed_string(ret_value, 1);
}

char* p_option(long int num)
{
    long int copy_num = num;
    long int count = 0;
    while (copy_num != 0)
    {
        count++;
        copy_num /= 10;
    }

    char* ret_value = calloc(sizeof(char), count + 1);
    int ind = 0;
    while (num != 0)
    {
        int reminder = num % 16;
        if (reminder < 10)
        {
            ret_value[ind++] = reminder + '0';
        }
        else
        {
            ret_value[ind++] = reminder + 55;
        }
        num /= 16;
    }

    return reversed_string(ret_value, 1);
}

char* o_option(int num)
{
    int copy_num = num;
    int count = 0;
    while (copy_num != 0)
    {
        count++;
        copy_num /= 10;
    }

    char* ret_value = calloc(sizeof(char), count + 1);
    int ind = 0;
    while (num != 0)
    {
        ret_value[ind++] = num % 8 + 48;
        num /= 8;
    }

    return reversed_string(ret_value, 1);
}

void find_ident(char* str, va_list* arg, int* i, int* summ)
{
    *i += 1;
    if (str[*i] == 'c')
    {
        char letter = va_arg(*arg, int);
        *summ += write(1, &letter, 1);
    }
    else if (str[*i] == 'd')
    {
        int flag = 1;
        int num = va_arg(*arg, int);
        if (num == 0)
        {
            char null = '0';
            *summ += write(1, &null, 1);
        }
        if (num < 0)
        {
            flag = 0;
        }
        char* str_num = my_atoi(num, flag);
        *summ += write(1, str_num, my_strlen(str_num));
        free(str_num);
    }
    else if (str[*i] == 's')
    {
        char* str_wr = va_arg(*arg, char*);
        if (str_wr == NULL)
        {
            char NLL[] = "(null)";
            *summ += write(1, NLL, 6);
            return;
        }
        *summ += write(1, str_wr, my_strlen(str_wr));
    }
    else if (str[*i] == 'u')
    {
        int u_num = va_arg(*arg, int);
        if (u_num < 0)
        {
            u_num *= -1;
        }
        char* str_num = my_atoi(u_num, 1);
        *summ += write(1, str_num, my_strlen(str_num));
        free(str_num);
    }
    else if (str[*i] == 'x')
    {
        int x_opt = va_arg(*arg, int);
        char* x_str = p_option(x_opt);
        *summ += write(1, x_str, my_strlen(x_str));
        free(x_str);
    }
    else if (str[*i] == 'p')
    {
        long int addr = va_arg(*arg, long int);
        char* my_str = x_option(addr);
        char OX[] = "0x";
        *summ += write(1, OX, 2);
        *summ += write(1, my_str, my_strlen(my_str));
        free(my_str);
    }
    else if (str[*i] == 'o')
    {
        int o_num = va_arg(*arg, int);
        char* o_str = o_option(o_num);
        *summ += write(1, o_str, my_strlen(o_str));
        free(o_str);
    }
}

int my_printf(char* str, ...)
{
    int summ = 0;
    va_list arg;
    va_start(arg, str);

    for (int i = 0; i < my_strlen(str); i++)
    {
        if (str[i] == '%')
        {
            find_ident(str, &arg, &i, &summ);
        }
        else
        {
            summ += write(1, &str[i], 1);
        }
    }
    return summ;
}

int main()
{
    return 0;
}