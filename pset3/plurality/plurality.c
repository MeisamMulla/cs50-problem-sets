#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            candidates[i].votes++;
            return true;
        }
    }

    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // create tmp candidate
    candidate tmp[1];

    // keep track of candidates with the same number of votes
    int same_votes = 1;

    // interate through all candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // iterate through the candidates once more and sort them (linear sort)
        for (int j = 0; j < candidate_count - i; j++)
        {
            // if the next ones votes are more than the current ones
            if (candidates[j].votes < candidates[j + 1].votes)
            {
                // set the current one to a temp
                tmp[0] = candidates[j];

                // put the values of the next one to the current one
                candidates[j] = candidates[j + 1];

                // put the tmp one's values into the next one
                candidates[j + 1] = tmp[0];
            }
        }
    }

    // run through the list again to determine how many ties we have
    for (int i = 0; i < candidate_count; i++)
    {
        printf("%s\n", candidates[i].name);

        // if the current vote count is greater than the next one just break out of the loop
        if (candidates[i].votes > candidates[i + 1].votes)
        {
            break;
        }
    }

    return;
}

