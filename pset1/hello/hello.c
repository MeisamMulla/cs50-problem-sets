#include <stdio.h>
#include <cs50.h>

int main(void) 
{
    // Prompt user for their name
    string name = get_string("What is your name? ");
    
    // Display their name along with a greeting
    printf("hello, %s\n", name);
}