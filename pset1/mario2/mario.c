#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n = 10;
    //Read while n is not in the interval
    while (n < 1 || n > 8)
    {
        n = get_int("Height: ");
    }

    //Inicialize variables

    int i = 0;
    int j = 0;

    //Print lines

    for (i=0;i<n;i++)
    {
        //Print Columns

        for (j=0;j<n-i-1;j++)
        {
            printf(" ");
        }

        for (j=0;j<i+1;j++)
        {
            printf("#");
        }

        printf("  ");

        for (j=0;j<i+1;j++)
        {
            printf("#");
        }

        printf("\n");

    }
}