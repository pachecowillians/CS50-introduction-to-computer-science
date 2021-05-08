// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
//Take a prime number
const unsigned int N = 7919;

// Hash table
node *table[N];

//Store the size of dictionary
int dicSize = 0;

//Convert the string to lowercase
void toLowercase(char *str)
{
    //Stops when find the \0
    for (int i = 0; str[i] != '\0'; i++)
    {
        //Only convert letters
        if (isalpha(str[i]))
        {
            str[i] = tolower(str[i]);
        }
    }
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //Create a new string
    char lowWord[LENGTH + 1];
    //Copy the word string to the not const string
    strcpy(lowWord, word);
    //Convert the new string
    toLowercase(lowWord);
    //Hash the lowecase string
    int v = hash(lowWord);
    //If there is nothing in the place of the hash of the string
    if (table[v] == NULL)
    {
        return false;
    }
    else
    {
        //Go trough the list until if ends searching for the word
        node *p = table[v];
        while (p != NULL)
        {
            if (strcmp(p->word, lowWord) == 0)
            {
                //When the word is found
                return true;
            }
            p = p->next;
        }
        return false;
    }

}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int prod = 1;
    //Multiply the number (integer correspondent of the letter) of each char
    for (int i = 0; word[i] != '\0'; i++)
    {
        prod *= (int)word[i];
    }
    //Return the product module by N (that is a prime number and the size of array)
    //The fact of N is prime, avoid colisions
    return prod % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[50];
    //Open the file
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        fclose(file);
        return false;
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            //Make the hash table null on the begin of program
            table[i] = NULL;
        }
        //Read the dictionary file
        while (fscanf(file, "%50s", word) == 1)
        {
            //Count the number of words
            dicSize++;
            int v = hash(word);
            //If there is not a "head" of the list, put the first node of list
            if (table[v] == NULL)
            {
                node *n = malloc(sizeof(node));
                strcpy(n->word, word);
                n->next = NULL;
                table[v] = n;
            }
            //Follow the list until the end and insert the new word
            else
            {
                node *p = table[v];
                while (p->next != NULL)
                {
                    p = p->next;
                }
                node *n = malloc(sizeof(node));
                strcpy(n->word, word);
                n->next = NULL;
                p->next = n;
            }
        }
        //Free the memory
        fclose(file);
        return true;
    }
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    //Return the number of words
    return dicSize;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //Go tough all the positions in the hast table
    for (int i = 0; i < N; i++)
    {
        node *p = table[i];
        node *f;
        //Follow each list, till the end and free the memory
        while (p != NULL)
        {
            //Store the next pointer
            f = p->next;
            //Free the atual pointer
            free(p);
            //Atualize the p value to the "next" be the atual
            p = f;
        }
    }
    //End the free proceess
    return true;
}
