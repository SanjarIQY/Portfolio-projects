#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int last_stars(int a)
{
    int max_star = 7;
    int step = 2;

    for(int i = 2; i <= a; i++)
    {
        int layer = i + 4 - 1;
        for(int j = 2; j <= layer; j++)
        {
            max_star += 2;            
        } 
        
        max_star -= step;

        if(i + 1 != 2 && (i +1) % 2 ==0)
        {
            step += 2;
        }

    }
    return max_star;
}

void print(int a)
{
    int step = 4;
    int minusP = 2;
    int minusT = 4;
    int space = last_stars(a) / 2;
    int star = 1;
    for(int i = 0; i < a; i++)
    {
        for(int j = 0; j < step; j++)
        {
            for(int k = 0; k < space; k++)
            {
                printf(" ");
                // printf("%d", space);
            }
            for(int k = 0; k < star; k++)
            {
                printf("*");
            }
            printf("\n");
            star += 2;
            space--;
            
            // printf("%d\n", space);
        }
         if(step % 2 == 0 && step != 4)
            {
                minusP++;
                minusT += 2;
            }
            space += minusP;
            star -= minusT;   
        step++;
    }
    
    int spacee = last_stars(a) / 2 - a / 2 ;
    if(a % 2 == 0) spacee++;
    

    for(int i = 0; i < a; i++)
    {
        for(int j = 0; j < spacee; j++)
            printf(" ");
        for(int k = 0; k < a; k++)
            printf("|");
        printf("\n");
    }
    
}

int main(int ac, char **av)
{
    int Chtree = atoi(av[1]);
    print(Chtree);
}