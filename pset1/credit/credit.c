#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Read number
    long n = get_long("Number: ");
    //Initialize variables
    int i = 0;
    int soma = 0;
    int soma2 = 0;
    int ultimoDigito = 0;
    //While the number is bigger than 10, it can be divided by 10
    while (n > 9)
    {
        //Take the 2 first numbers
        if (n < 100)
        {
            ultimoDigito = n;
        }
        int v = n % 10;
        if (i % 2 == 0)
        {
            soma += v;
        }
        else
        {
            v *= 2;
            //Sum digits
            if (v > 9)
            {
                soma2 += v % 10;
                v /= 10;
            }
            soma2 += v;
        }
        n /= 10;
        i++;
    }
    //Repeat code for the last number
    int v = n % 10;
    if (i % 2 == 0)
    {
        soma += v;
    }
    else
    {
        //Sum digits
        v *= 2;
        if (v > 9)
        {
            soma2 += v % 10;
            v /= 10;
        }
        soma2 += v;
    }
    i++;
    //Conditionals to inform the card kind
    if ((soma + soma2) % 10 != 0)
    {
        //If the sum is not divided by zero
        printf("INVALID\n");
    }
    else if (ultimoDigito / 10 == 4 && (i == 13 || i == 16))
    {
        //The ideal condition to be a visa card
        printf("VISA\n");
    }
    else if ((ultimoDigito == 51 || ultimoDigito == 52 || ultimoDigito == 53 || ultimoDigito == 54 || ultimoDigito == 55) && (i == 16))
    {
        //The ideal condition to be a master card
        printf("MASTERCARD\n");
    }
    else if ((ultimoDigito == 34 || ultimoDigito == 37) && (i == 15))
    {
        //The ideal condition to be a amex card
        printf("AMEX\n");
    }
    else
    {
        //If it is not any kind of card, it is invalid
        printf("INVALID\n");
    }

}