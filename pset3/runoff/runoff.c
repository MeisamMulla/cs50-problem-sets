#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // iterate through candidates based on candidate_count
    for (int i = 0; i < candidate_count; i++)
    {
        // check if name matches candidates name
        if (strcmp(candidates[i].name, name) == 0)
        {
            // record preference
            preferences[voter][rank] = i;
            return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // iterate by the number of voters
    for (int i = 0; i < voter_count; i++)
    {
        // for each voter iterate by the number of candidates
        for (int j = 0; j < candidate_count; j++)
        {
            // if the candidate isnt eliminated yet
            if (!candidates[preferences[i][j]].eliminated)
            {
                // add to their votes
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    bool winner = false;
    float majority = voter_count / 2;

    string winner_name;

    // iterate based on the number of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if candidates votes/voter count are greater than 50 they are the winner
        if ((float) candidates[i].votes > majority)
        {
            winner_name = candidates[i].name;
            winner = true;
        }
    }

    // for (int i = 0; i < candidate_count; i++)
    // {
    //     printf("c: %s, v: %i, e: %d\n", candidates[i].name, candidates[i].votes, candidates[i].eliminated);
    // }

    if (winner)
    {
        printf("%s\n", winner_name);
        return true;
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // start off with the number of voters we have and reduce
    int min = voter_count;

    // iterate based on the number of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidates has a lower score than min & they are not eliminated
        if (candidates[i].votes < min && !candidates[i].eliminated)
        {
            min = candidates[i].votes;
        }
    }

    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // candidates left
    int c_left = 0;
    // candidates above min left
    int m_left = 0;

    // iterate based on the number of candidates
    for (int i = 0; i < candidate_count - 1; i++)
    {
        // if the candidate hasnt been elimninated add to c_left
        if (!candidates[i].eliminated)
        {
            c_left++;
        }

        // if this candidates votes are the same as min add to m_left
        if (candidates[i].votes == min)
        {
            m_left++;
        }
    }

    // if c_left matches m_left we can say they are all tied
    if (c_left == m_left)
    {
        return true;
    }


    // TODO
    return false;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // iterate based on the number of candidates
    for (int i = 0; i < candidate_count; i++)
    {
        // if the candidates votes matches min then eliminate them
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }

    // TODO
    return;
}
