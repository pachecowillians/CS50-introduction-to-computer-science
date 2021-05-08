#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Keep the values in float variables
            float r = image[i][j].rgbtRed;
            float g = image[i][j].rgbtGreen;
            float b = image[i][j].rgbtBlue;
            //Calc the average
            //Use the round to round the value to the near integer
            int v = round((r + g + b) / (float)3);
            //Assign the value to the collors attributes
            image[i][j].rgbtBlue = v;
            image[i][j].rgbtGreen = v;
            image[i][j].rgbtRed = v;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Flip the image vertically
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //Use the entire type to swap the values together in the struct
            //Width - 1 because the value in vector is decreased by 1
            RGBTRIPLE aux = image[i][width - 1 - j];
            image[i][width - 1 - j] = image[i][j];
            image[i][j] = aux;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Copy the image original to a new image in memory to don't change the original image
            original[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // On the top left corner
            if (i == 0 && j == 0)
            {
                image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i][j + 1].rgbtBlue +
                                                     original[i + 1][j + 1].rgbtBlue) / (float)4);
                image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i][j + 1].rgbtGreen +
                                                      original[i + 1][j + 1].rgbtGreen) / (float)4);
                image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i][j + 1].rgbtRed +
                                                    original[i + 1][j + 1].rgbtRed) / (float)4);
            }
            //On the top right corner
            else if (i == 0 && j == width - 1)
            {
                image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i][j - 1].rgbtBlue +
                                                     original[i + 1][j - 1].rgbtBlue) / (float)4);
                image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i][j - 1].rgbtGreen +
                                                      original[i + 1][j - 1].rgbtGreen) / (float)4);
                image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i][j - 1].rgbtRed +
                                                    original[i + 1][j - 1].rgbtRed) / (float)4);
            }
            //On the bottom right corner
            else if (i == height - 1 && j == width - 1)
            {
                image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i][j - 1].rgbtBlue +
                                                     original[i - 1][j - 1].rgbtBlue) / (float)4);
                image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i][j - 1].rgbtGreen +
                                                      original[i - 1][j - 1].rgbtGreen) / (float)4);
                image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i][j - 1].rgbtRed +
                                                    original[i - 1][j - 1].rgbtRed) / (float)4);
            }
            //On the bottom left corner
            else if (i == height - 1 && j == 0)
            {
                image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i][j + 1].rgbtBlue +
                                                     original[i - 1][j + 1].rgbtBlue) / (float)4);
                image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i][j + 1].rgbtGreen +
                                                      original[i - 1][j + 1].rgbtGreen) / (float)4);
                image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i][j + 1].rgbtRed +
                                                    original[i - 1][j + 1].rgbtRed) / (float)4);
            }
            //On the first line
            else if (i == 0)
            {
                image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i + 1][j].rgbtBlue + original[i][j - 1].rgbtBlue +
                                                     original[i][j + 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue +
                                                     original[i + 1][j + 1].rgbtBlue) / (float)6);
                image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i + 1][j].rgbtGreen + original[i][j - 1].rgbtGreen +
                                                      original[i][j + 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen +
                                                      original[i + 1][j + 1].rgbtGreen) / (float)6);
                image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i + 1][j].rgbtRed + original[i][j - 1].rgbtRed +
                                                    original[i][j + 1].rgbtRed + original[i + 1][j - 1].rgbtRed +
                                                    original[i + 1][j + 1].rgbtRed) / (float)6);
            }
            //On the last line
            else if (i == height - 1)
            {
                image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i - 1][j].rgbtBlue + original[i][j - 1].rgbtBlue +
                                                     original[i][j + 1].rgbtBlue + original[i - 1][j - 1].rgbtBlue +
                                                     original[i - 1][j + 1].rgbtBlue) / (float)6);
                image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i - 1][j].rgbtGreen + original[i][j - 1].rgbtGreen +
                                                      original[i][j + 1].rgbtGreen + original[i - 1][j - 1].rgbtGreen +
                                                      original[i - 1][j + 1].rgbtGreen) / (float)6);
                image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i - 1][j].rgbtRed + original[i][j - 1].rgbtRed +
                                                    original[i][j + 1].rgbtRed + original[i - 1][j - 1].rgbtRed +
                                                    original[i - 1][j + 1].rgbtRed) / (float)6);
            }
            //On the first column
            else if (j == 0)
            {
                image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i][j + 1].rgbtBlue + original[i - 1][j].rgbtBlue +
                                                     original[i + 1][j].rgbtBlue + original[i - 1][j + 1].rgbtBlue +
                                                     original[i + 1][j + 1].rgbtBlue) / (float)6);
                image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i][j + 1].rgbtGreen + original[i - 1][j].rgbtGreen +
                                                      original[i + 1][j].rgbtGreen + original[i - 1][j + 1].rgbtGreen +
                                                      original[i + 1][j + 1].rgbtGreen) / (float)6);
                image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i][j + 1].rgbtRed + original[i - 1][j].rgbtRed +
                                                    original[i + 1][j].rgbtRed + original[i - 1][j + 1].rgbtRed +
                                                    original[i + 1][j + 1].rgbtRed) / (float)6);
            }
            //On the last column
            else if (j == width - 1)
            {
                image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i - 1][j].rgbtBlue +
                                                     original[i + 1][j].rgbtBlue + original[i - 1][j - 1].rgbtBlue +
                                                     original[i + 1][j - 1].rgbtBlue) / (float)6);
                image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i - 1][j].rgbtGreen +
                                                      original[i + 1][j].rgbtGreen + original[i - 1][j - 1].rgbtGreen +
                                                      original[i + 1][j - 1].rgbtGreen) / (float)6);
                image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i - 1][j].rgbtRed +
                                                    original[i + 1][j].rgbtRed + original[i - 1][j - 1].rgbtRed +
                                                    original[i + 1][j - 1].rgbtRed) / (float)6);
            }
            //In the middle of the image
            else
            {
                image[i][j].rgbtBlue = round((float)(original[i][j].rgbtBlue + original[i][j - 1].rgbtBlue + original[i - 1][j].rgbtBlue +
                                                     original[i + 1][j].rgbtBlue + original[i - 1][j - 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue +
                                                     original[i + 1][j + 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue +
                                                     original[i][j + 1].rgbtBlue) / (float)9);
                image[i][j].rgbtGreen = round((float)(original[i][j].rgbtGreen + original[i][j - 1].rgbtGreen + original[i - 1][j].rgbtGreen +
                                                      original[i + 1][j].rgbtGreen + original[i - 1][j - 1].rgbtGreen +
                                                      original[i + 1][j - 1].rgbtGreen + original[i + 1][j + 1].rgbtGreen +
                                                      original[i - 1][j + 1].rgbtGreen + original[i][j + 1].rgbtGreen) / (float)9);
                image[i][j].rgbtRed = round((float)(original[i][j].rgbtRed + original[i][j - 1].rgbtRed + original[i - 1][j].rgbtRed +
                                                    original[i + 1][j].rgbtRed + original[i - 1][j - 1].rgbtRed + original[i + 1][j - 1].rgbtRed +
                                                    original[i + 1][j + 1].rgbtRed + original[i - 1][j + 1].rgbtRed +
                                                    original[i][j + 1].rgbtRed) / (float)9);
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //To create a border (1px on each side)
    height += 2;
    width += 2;
    //Create a matrix to store the original image with border
    RGBTRIPLE original[height][width];
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
            {
                //If it is in border, set to black (0)
                original[i][j].rgbtBlue = 0;
                original[i][j].rgbtGreen = 0;
                original[i][j].rgbtRed = 0;
            }
            else
            {
                //Else, just copy the image
                //Position - 1 because the border is 1px greater than image, so change by 1 the image's position
                original[i][j] = image[i - 1][j - 1];
            }
        }
    }

    //-1 to don't count the borders
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            float gx = (-1) * original[i - 1][j - 1].rgbtBlue + original[i - 1][j + 1].rgbtBlue + (-2) * original[i][j - 1].rgbtBlue +
                       (2) * original[i][j + 1].rgbtBlue + (-1) * original[i + 1][j - 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue;
            float gy = (-1) * original[i - 1][j - 1].rgbtBlue + original[i + 1][j - 1].rgbtBlue + (-2) * original[i - 1][j].rgbtBlue +
                       (2) * original[i + 1][j].rgbtBlue + (-1) * original[i - 1][j + 1].rgbtBlue + original[i + 1][j + 1].rgbtBlue;
            //Round to the near integer
            int v = round(sqrt(pow(gx, 2) + pow(gy, 2)));
            //Set the max value to 255
            image[i - 1][j - 1].rgbtBlue = (v > 255) ? 255 : v;

            gx = (-1) * original[i - 1][j - 1].rgbtGreen + original[i - 1][j + 1].rgbtGreen + (-2) * original[i][j - 1].rgbtGreen +
                 (2) * original[i][j + 1].rgbtGreen + (-1) * original[i + 1][j - 1].rgbtGreen + original[i + 1][j + 1].rgbtGreen;
            gy = (-1) * original[i - 1][j - 1].rgbtGreen + original[i + 1][j - 1].rgbtGreen + (-2) * original[i - 1][j].rgbtGreen +
                 (2) * original[i + 1][j].rgbtGreen + (-1) * original[i - 1][j + 1].rgbtGreen + original[i + 1][j + 1].rgbtGreen;
            //Round to the near integer
            v = round(sqrt(pow(gx, 2) + pow(gy, 2)));
            //Set the max value to 255
            image[i - 1][j - 1].rgbtGreen = (v > 255) ? 255 : v;

            gx = (-1) * original[i - 1][j - 1].rgbtRed + original[i - 1][j + 1].rgbtRed + (-2) * original[i][j - 1].rgbtRed +
                 (2) * original[i][j + 1].rgbtRed + (-1) * original[i + 1][j - 1].rgbtRed + original[i + 1][j + 1].rgbtRed;
            gy = (-1) * original[i - 1][j - 1].rgbtRed + original[i + 1][j - 1].rgbtRed + (-2) * original[i - 1][j].rgbtRed +
                 (2) * original[i + 1][j].rgbtRed + (-1) * original[i - 1][j + 1].rgbtRed + original[i + 1][j + 1].rgbtRed;
            //Round to the near integer
            v = round(sqrt(pow(gx, 2) + pow(gy, 2)));
            //Set the max value to 255
            image[i - 1][j - 1].rgbtRed = (v > 255) ? 255 : v;
        }
    }
    return;
}
