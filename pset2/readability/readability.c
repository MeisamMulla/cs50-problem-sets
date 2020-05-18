#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string s = get_string("Text: ");

    int letters = 0;
    int words = 0;
    int sentences = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        // Add to the letters if its bettwen upper case a and lower case z
        if (s[i] >= 'A' && s[i] <= 'z')
        {
            // assumption that if the first letter is an alphabet character the first word has started
            if (i == 0)
            {
                words++;
            }

            letters++;
        }

        // Add to words if we have a space
        if (s[i] == ' ')
        {
            // make sure next letter is also not a space
            if (s[i + 1] != ' ')
            {
                words++;
            }
        }

        // Add to sentence if we have a . ! or a ?
        if (s[i] == '.' || s[i] == '!' || s[i] == '?')
        {
            sentences++;
        }
    }

    // printf("\n\n\n\n%i letters, %i words, %i sentences\n\n", letters, words, sentences);


    // Calculate the Coleman-Liau index
    float index = 0.0588 * (100.0 * letters / words) - 0.296 * (100.0 * sentences / words) - 15.8;

    // printf("%f\n", index);÷

    if (index < 1)
    {
        printf("Before Grade 1\n");
        return 0;
    }

    if (index >= 16)
    {
        printf("Grade 16+\n");
        return 0;
    }

    printf("Grade %.0d\n", (int) round(index));
}