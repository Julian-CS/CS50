#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (!strcmp(name, candidates[i]));
        {
            ranks[rank] = i;
            return true;
        }

    }
    return false;
}

// preferences[i][j] is number of voters who prefer i over j
// Update preferences given one voter's ranks [Specific candidate x][number of people who prefer that candidate over this y candidate]
void record_preferences(int ranks[])
{
    int count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < ranks[i]; j++)
        {
           prefrences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
           if (prefrences[i][j] > prefrences[j][i])
           {
               pairs[i].winner = i;
               pairs[i].loser = j;
               pair_count++;
           }
           if (prefrences[i][j] < prefrences[j][i])
           {
               pairs[i].winner = j;
               pairs[i].loser = i;
               pair_count++;
           }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory (selection sort or merge sort)
void sort_pairs(void)
{
    int candidate;
    int margin;
    int biggest;
    int place = 0;
    int count = 0;
    pair buffer;
    bool sorted = false;
    //find candidate with smallest margin of victory in array -> i = candidate pair
    while(sorted == false)
    {
        for (int i = place; i < candidate_count; place++)
        {
            int W_strength = prefrences[pairs[i].winner][pairs[i].loser];
            int L_strength = prefrences[pairs[i].loser][pairs[i].winner];

            //how many people preffered winner/loser - loser/winner
            margin = prefrences[W_strength][L_strength] - prefrences[L_strength][W_strength];

            if (i == 0)
            {
                biggest = margin;
                candidate = i;

            }
            if (biggest < margin)
            {
                biggest = margin;
                candidate = i;
            }
        }
        //swap lowest candidate with first candidate
        buffer = pairs[count];
        pairs[count] = pairs[candidate];
        pairs[candidate] = buffer;
        count++;
        place = count;

        if (count == candidate_count)
        {
            sorted = true;
        }
    }
    return;
}


//BRUH
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{



    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

