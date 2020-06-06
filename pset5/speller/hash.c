#include <stdio.h>
#include <cs50.h>

#define MAX 26

unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;

    int c;

    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash % MAX;
}



int main(void)
{
    while (true)
    {
        printf("String: ");

        unsigned char item[26];
        scanf("%s", item);

        printf("Hash: %lu\n", hash(item));
    }
}

