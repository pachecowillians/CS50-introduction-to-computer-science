#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

// Function to count letters
int CountLetters(string s)
{
    int n = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        //Verify if the character is a letter
        if (isalpha(s[i]))
        {
            n++;
        }
    }
    return n;
}

//Count the words in the text
int CountWords(string s)
{
    int n = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        //Verify if is a space and count the spaces
        if (s[i] == ' ')
        {
            n++;
        }
    }
    return n;
}

//Count the number of sentences in the text
int CountSentences(string s)
{
    int n = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        //The sentence ends with '.','!' or '?'
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            n++;
        }
    }
    return n;
}

//Calc the index with the formula
float CalcIndex(float l, float s)
{
    return 0.0588 * l - 0.296 * s - 15.8;
}

int main()
{
    string text = get_string("Text: ");
    float L = CountLetters(text);
    float W = CountWords(text) + 1; //The number of words is the number of spaces plus one
    float S = CountSentences(text);

    //Calc the index and round it to the near integer
    int i = round(CalcIndex(100 * L / W, 100 * S / W));

    if (i < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (i >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", i);
    }
}