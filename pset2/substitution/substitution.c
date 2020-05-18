#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void print_help(string program);
int validate_key(string key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        print_help(argv[0]);
        return 1;
    }

    string key = argv[1];

    // validate the key
    switch (validate_key(key))
    {
        case 0:
            printf("Key must only have letters.\n");
            return 1;

        case -1:
            printf("Key must not contain the same character more than once.\n");
            return 1;

        case -2:
            printf("Key must contain 26 characters.\n");
            return 1;
    }

    // convert the key to all uppercase
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        key[i] = toupper(key[i]);
    }

    // get the input from the user
    string plaintext = get_string("plaintext: ");
    string ciphertext = plaintext;

    // iterate through each letter and apply the cipher
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // check to make sure item is a letter
        if (isalpha(plaintext[i]))
        {
            int start;
            bool upper = false;

            // if character is upper case set start to 65 from ascii
            if (isupper(plaintext[i]))
            {
                start = 65;
                // set upper flag to true
                upper = true;
            }
            else
            {
                // otherwise set start to ascii 97
                start = 97;
            }

            // find the corresponding cipher in the key
            int find = (plaintext[i] - start) % 26;

            // if the upper flat was set earlier just replace it with the substitution
            if (upper)
            {
                ciphertext[i] = key[find];
            }
            else
            {
                // otherwise convert the character to lowercase
                ciphertext[i] = tolower(key[find]);
            }
        }
    }

    printf("ciphertext: %s\n", ciphertext);
}

void print_help(string program)
{
    printf("Usage: %s key\n", program);
}

// Validate the key, make sure it is 26 characters, and doesnt have any numbers and also doesnt have any duplicate characters
int validate_key(string key)
{

    if (strlen(key) != 26)
    {
        return -2;
    }

    // iterate through each item in the key array
    for (int i = 0, n = strlen(key); i < n; i ++)
    {
        // set current key
        char current_key = key[i];

        // check if key is a non letter
        if (!isalpha(current_key))
        {
            return 0;
        }

        // iterate through all keys in the array
        for (int j = 0; j < 26; j++)
        {
            // make sure we're not looking at the same position
            if (j != i)
            {
                // return false if we find the key more than once
                if (current_key == key[j])
                {
                    return -1;
                }
            }
        }
    }

    return 1;
}