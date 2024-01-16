#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// int arr_length(char **p)
// {
//     int sum = 0;
//     for (int i = 1; p[i]; i++)
//     {
//         int j = 0;
//         while (p[i][j])
//         {
//             j++;
//             sum++;
//         }
//     }
//     return sum;
// }

// char *check(char **argv)
// {
//     int k = 0, j = 0;
//     char *all = malloc(sizeof(char) * arr_length(argv));
//     for (int i = 1; argv[i]; i++)
//     {
//         for (k = 0; argv[i][k]; k++) all[j++] = argv[i][k];
//     }
//     return all;
// }

// void sort(char *p1)
// {
//     char *res = malloc(sizeof(char) * strlen(p1));
//     for (int i = 0; p1[i]; i++)
//     {
//         res[i] = p1[i];
//     }
//     // printf("%s\n", res);
//     int count = 1;
//     int arr[128] = {0};
//     char *temp;
//     int k = 0;
//     int length = strlen(res);

//     for (int i = 0; res[i]; i++)
//     {
//         temp = malloc(sizeof(char) * strlen(res));
//         count = 1;
//         for (int j = i + 1; res[j]; j++)
//         {
//             if (res[i] == res[j])
//                 count++;
//             else
//             {
//                 temp[k++] = res[j];
//             }
//         }
//         printf("%s\n", res);
//         arr[(int)res[i]] = count;
//         free(res);
//         res = temp;
//         i--;
//         k = 0;
//     }

//     for (int i = 0; i < 128; i++)
//     {
//         if (arr[i] != 0) printf("%c:%d\n", i, arr[i]);
//     }
// }


void check(char *a){
    int str[128] = {0};
    for(int i = 0; a[i]; i++){
        str[a[i]]++;
    }
    
    for (int i = 0; i < 128; i++)
    {
        if(str[i] != 0) printf("%c:%d\n", i, str[i]);
    }
}

int main(int argc, char **argv)
{
    if (argc == 0) return 0;
    

    check(argv[1]);
    // printf("%s", str);
    // printf("%d -> %s", length, str);
}
