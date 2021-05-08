#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    //Go trough the candidate's array and check if the name exists
    for (int i = 0; i < candidate_count; i++)
    {
        //If the name exists, set ranks[rank] to the index of candidate
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    //If does not exists, return false
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        //i + 1 because only the column i+1> is less preferred than the candidate i
        for (int j = i + 1; j < candidate_count; j++)
        {
            //Link every candidade to whom is below him
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        //i + 1 for optimize the code, and do not go trough unnecessary columns, since i compare the column [i][j] with [j][i]
        for (int j = i + 1; j < candidate_count; j++)
        {
            //Choose the bigger and discard when it is equal
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair aux;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            //Common sort, just check if is greather and swap the pairs
            if (preferences[pairs[i].winner][pairs[i].loser] > preferences[pairs[j].winner][pairs[j].loser])
            {
                aux = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = aux;
            }
        }
    }
    return;
}

//Recursive function to verify if there is a cycle in the graph

bool VerifyCycle(int l, int m)
{
    bool r = false;
    //Go trough the entire column and check the links, and if it falls in a loop, it will count until a value, and if pass the value, it recognize that is a loop
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[l][j] && m > 0)
        {
            //If there is a link
            r =  VerifyCycle(j, m - 1);
            if (r)
            {
                //If i found that exists a cycle in another recoursive call
                return r;
            }
        }
        else if (m <= 0)
        {
            //If it falls into a loop
            return true;
        }
    }
    return r;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        //To every ordened pair, create the link, and if the link creates a loop, remove the link
        if (VerifyCycle(pairs[i].winner, 2 * candidate_count))
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int j = 0; j < candidate_count; j++)
    {
        bool winner = true;
        //Just check if there is a column all false in the graph's matrix, and consider that the candidat whom this column represents is the source node, or the winner.
        for (int i = 0; i < candidate_count && winner; i++)
        {
            if (locked[i][j])
            {
                winner = false;
            }
        }
        if (winner)
        {
            //If the candidat is the winner, print his name
            printf("%s\n", candidates[j]);
        }
    }
    return;
}

