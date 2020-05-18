#include <stdio.h>
#include <cs50.h>


int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    // Make sure the height is greater than 1 but lower than 8
    while (height < 1 || height > 8);

    // draw height lines
    for (int i = 0; i < height; i++)
    {
        // first set of the pyramid
        for (int j = 0; j < height; j++)
        {
            if (i >= height - (j + 1)) 
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }

        // Leave some space
        printf("  ");


        // Second part of the pyramid
        for (int j = 0; j < height; j++)
        {
            if (i >= j) 
            {
                printf("#");
            }
        }

        // lets move to the next line
        printf("\n");
    }
}