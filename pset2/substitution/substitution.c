#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

//Function to verify if the key is valid or not
bool VerifyKey(string s)
{

    if (strlen(s) != 26) //The key is invalid if the length is different than 26
    {
        return false;
    }
    else
    {
        bool v[26]; // An array to verify if there is a letter repeated
        for (int i = 0; i < 26; i++)
        {
            v[i] = false; //Setting the array to false
        }
        for (int i = 0; i < 26; i++)
        {
            if (!isalpha(s[i])) //If the key contains anything that is not letters, it is invalid
            {
                return false;
            }
            else
            {
                int p = tolower(s[i]) - 'a'; //The position in the key string
                if (!v[p])
                {
                    v[p] = true;
                }
                else
                {
                    return false;
                }
            }
        }
        return true;
    }
}

//Apply the key in the string to cryptograph
string ConvertString(string s, string key)
{

    for (int i = 0; i < strlen(s); i++)
    {
        if (isalpha(s[i])) //Only apply the key in the letters
        {
            if (isupper(s[i]))//Keep the uppercase in uppercase, and lowercase in lowercase
            {
                s[i] =  toupper(key[tolower(s[i]) - 'a']);
            }
            else
            {
                s[i] =  tolower(key[tolower(s[i]) - 'a']);
            }
        }
    }
    return s;
}

int main(int argc, string argv[])
{
    if (argc == 2) //If is just one argument passed to the program via command-line
    {
        string s = argv[1];
        if (!VerifyKey(s)) //If the key is invalid
        {
            printf("Invalid Key!");
            return 1;
        }
        else //If everything is okay, just convert the string and show
        {
            string strInput = get_string("plaintext: ");
            printf("ciphertext: %s\n", ConvertString(strInput, s));
        }
    }
    else //If is not the key correct
    {
        printf("Missing the key, or too many keys!\n");
        return 1;
    }
}