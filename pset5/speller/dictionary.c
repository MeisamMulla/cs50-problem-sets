// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 50;

unsigned int dict_size = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // get the hash
    unsigned int h = hash(word);

    // iterate through the linked list if there is one
    for (node *tmp = table[h]; tmp != NULL; tmp = tmp->next)
    {
        // compare the words case insensitive
        if (strcasecmp(word, tmp->word) == 0)
        {
            return true;
        }
    }

    // TODO
    return false;
}

// Hashes word to a number
// djb2 hashing algorithm by Dan Bernstein
// taken from http://www.cse.yorku.ca/~oz/hash.html
// inspired by https://gist.github.com/vkWeb/1e713853124c9f869df1a456699bfe22
unsigned int hash(const char *word)
{
    unsigned int hash = 5381;
    int c;

    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");

    if (!dict)
    {
        return false;
    }

    char string[LENGTH + 1];
    unsigned int h;

    while (fscanf(dict, "%s", string) != EOF)
    {
        // assign memory for node
        node *n = calloc(1, sizeof(node));

        // check if memory assigned
        if (!n)
        {
            return false;
        }

        // copy word to node
        strcpy(n->word, string);

        // get the hash of the word
        h = hash(string);

        // if the row is empty make it the first item
        if (table[h] == NULL)
        {
            table[h] = n;
        }
        else
        {
            n->next = table[h];
            table[h] = n;
        }

        // increment the dict_size counter
        dict_size++;

    }

    fclose(dict);

    // TODO
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // just return the dict_size since we kept track of it when adding it to the hashtable
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int counter = 0;

    // iterate based on the number of N
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            // store the next item to tmp
            node *tmp = table[i]->next;

            // free the memory of the current node
            free(table[i]);

            // set the value to tmp's
            table[i] = tmp;
        }

        // if the table is empty increment the counter
        if (table[i] == NULL)
        {
            counter++;
        }
    }

    if (counter == N)
    {
        return true;
    }

    return false;
}
