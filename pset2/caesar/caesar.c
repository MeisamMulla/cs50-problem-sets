#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    // Check to make sure that only the key is set
    if (argc != 2)
    {
        printf("Usage %s key\n", argv[0]);
        return 1;
    }

    // Go through the key and make sure its just numeric. If not return with help message
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (argv[1][i] < 48 || argv[1][i] > 58)
        {
            printf("Usage %s key\n", argv[0]);
            return 1;
        }
    }

    // convert the offset into an integer
    int offset = atoi(argv[1]);

    // get the string from the user
    string plain = get_string("plaintext: ");

    int n = strlen(plain);

    for (int i = 0; i < n; i++)
    {
        // make sure its alphabetical
        if (isalpha(plain[i]))
        {
            int start_at;

            // start at 65 on ascii if its uppercase
            if (isupper(plain[i]))
            {
                start_at = 65;
            }
            else
                // or 97 if lowercase
            {
                start_at = 97;
            }

            // map it to 0 so instead of A = 65, A = 0
            int make_zero = plain[i] - start_at;

            // key = (p[i] + k) % 26
            int key = (make_zero + offset) % 26;

            // Add back the start at we took out
            plain[i] = key + start_at;

        }
    }

    printf("ciphertext: %s\n", plain);
}