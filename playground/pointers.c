#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void)
{
    char *string = get_string("String: ");

    // allocate memory of the length of string + 1 for null terminator
    char *uppercase = malloc(strlen(string) + 1);

    printf("%s is the string inputted.\n", string);

    // Going to copy the null terminator character as well hence the <=
    for (int i = 0, n = strlen(string); i <= n; i++)
    {
        uppercase[i] = string[i];
    }

    uppercase[0] = toupper(string[0]);

    printf("%s is the string capitalized\n", uppercase);

    // free the memory assigned
    free(uppercase);
}