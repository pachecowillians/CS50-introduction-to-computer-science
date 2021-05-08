#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Reads the name of user
    string name = get_string("What is your name?\n");
    //Show in the screen hello to the user
    printf("hello, %s\n", name);
}