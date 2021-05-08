#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //If there are more than one argument (the file name) in command-line
    if (argc == 2)
    {
        //Openning the card.raw file
        FILE *file = fopen(argv[1], "r");
        //If the program can open the file
        if (file)
        {
            //Creating an array of bytes
            BYTE bytes[512];
            int i = 0;
            FILE *img;
            //Read from card blocks of 512 bytes, once per time and store em bytes array
            while (fread(&bytes, 512, 1, file))
            {
                //If the file begins like the jpeg's file
                if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && ((bytes[3] & 0xf0) == 0xe0))
                {
                    //The last condition verify if is 0xe and something
                    //Define a file name
                    char filename[9];
                    //If there is a file open
                    if (i > 0)
                    {
                        fclose(img);
                    }
                    //Print in a string with format. Three numbers, and fill with zeros
                    sprintf(filename, "%03i.jpg", i);
                    //Open a new file to store a image
                    img = fopen(filename, "w");
                    i++;
                }
                if (i > 0)
                {
                    //write the bytes in the image that is open
                    fwrite(bytes, 512, 1, img);
                }
            }
        }
        else
        {
            //If can't open the image
            printf("Usage: ./recover image\n");
            return 1;
        }
    }
    else
    {
        //If the number of parameters in command-line is wrong
        printf("Usage: ./recover image\n");
        return 1;
    }
}
