#include "helpers.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = round(((float) image[i][j].rgbtRed + (float) image[i][j].rgbtGreen + (float) image[i][j].rgbtBlue) / 3);

            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float colors[3] = {};

            colors[0] = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            colors[1]  = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            colors[2]  = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            for (int k = 0; k < 3; k++)
            {
                if (colors[k] > 255)
                {
                    colors[k] = 255;
                }
                else
                {
                    colors[k] = round(colors[k]);
                }
            }

            image[i][j].rgbtRed = colors[0];
            image[i][j].rgbtGreen = colors[1];
            image[i][j].rgbtBlue = colors[2];
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = width / 2; j < n; j++)
        {
            // the opposite of this one will be
            int ant = (width - 1) - j;

            // create a new temp var
            RGBTRIPLE row = {};

            // save the currents values into tmp
            row = image[i][j];

            // replace the currents value with the ant
            image[i][j] = image[i][ant];

            //transfer the values from tmp to the ant
            image[i][ant] = row;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a tmp image because otherwise the colors will be off
    RGBTRIPLE tmp[height][width];

    // loop through each row
    for (int i = 0; i < height; i++)
    {
        // loop through each column
        for (int j = 0; j < width; j++)
        {
            // store the colors
            float red = 0;
            float green = 0;
            float blue = 0;

            // keep track of neighbours for later
            int neighbour = 0;

            // start from the top
            for (int k = -1; k < 2; k++)
            {
                // then to the left
                for (int l = -1; l < 2; l++)
                {
                    // is row and top greater than or eq to 0, row and top less than the height,
                    // column and left greater than or equal to 0, column and left less than the width
                    if ((i + k) >= 0 && (i + k) < height && (j + l) >= 0 && (j + l) < width)
                    {
                        red += image[i + k][j + l].rgbtRed;
                        green += image[i + k][j + l].rgbtGreen;
                        blue += image[i + k][j + l].rgbtBlue;
                        neighbour++;
                    }
                }
            }

            tmp[i][j].rgbtRed = round(red / (float) neighbour);
            tmp[i][j].rgbtGreen = round(green / (float) neighbour);
            tmp[i][j].rgbtBlue = round(blue / (float) neighbour);
        }

    }

    // transfer the tmp image to the real image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }

    return;
}
