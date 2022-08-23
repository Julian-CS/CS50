#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>

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
bool has_cycle(int index);
bool helper(int index, bool visited[]);
int compare(const void *p1, const void *p2);

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
        if (!strcmp(name, candidates[i]))
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
        for (int j = i + 1; j < candidate_count; j++)
        {
           preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
           if (preferences[i][j] > preferences[j][i])
           {
               pair p;
               p.winner = i;
               p.loser = j;
               pairs[pair_count++] = p;
           }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory (selection sort or merge sort)
void sort_pairs(void)
{

    qsort(pairs, pair_count, sizeof(pair), compare);
    return;
}

int compare(const void *p1, const void *p2)
{
    //Typecast void* to pair* then derefrence that to get local copy p1/p2
    pair pn1 = *((pair*) p1);
    pair pn2 = *((pair*) p2);


    //find margin of victory of one candidate 3-2 over 2-3 (3/2 - 2/3)
    //positive number/ biggest number is stronger victory
    int first_strength = preferences[pn1.winner][pn1.loser] - preferences[pn1.loser][pn1.winner];
    int second_strength = preferences[pn2.winner][pn2.loser] - preferences[pn2.loser][pn2.winner];

    //return the thing that gets compared wth next element
    return second_strength - first_strength;
}



//BRUH
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    /*pseudo code
        1.check first pair and check if loser leads to a previous winner
        2. if winner then Follow that pair back and see if a loop gets created
        3. If loop then don't lock in that pair
        4. If not then lock pair

        Recursively call check cycle function
        Look at a pair
        If the loser is not a winner in any existing locked pair, then lock the pair
        If the loser is a winner in an existing locked pair:
            Look at that pair
        If the loser is not a winner in any existing locked pair, then lock the pair
        If the loser is a winner in an existing locked pair:
        Look at that pair
    */


    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;

        if(has_cycle(i))
            locked[pairs[i].winner][pairs[i].loser] = false;
    }

    return;
}

bool helper(int index, bool visited[])
{
    //if it has a cycle then we will be back at a previously visited candidate
    if (visited[index] == true)
    {
        return true;
    }

    //Mark that the current candidate has been visited
    visited[index] = true;


    //check if index candidate is ever a winner
    for (int i = 0; i < candidate_count; i++)
    {
            //checck if this candidate is ever a winner and next edge creates a cycle recursively
        if (locked[index][i] && helper(i, visited))
        {
            return true;
        }
    }

    //no cycle
    return false;
}

//check if pair (i) has a cycle
bool has_cycle(int index)
{
    bool visited[candidate_count];
    for (int j = 0; j < candidate_count; j++)
    {
        visited[j] = false;
    }
    return helper(index, visited);
}

// Print the winner of the election
void print_winner(void)
{
    bool head;
    int winner;
    for (int i = 0; i < candidate_count; i++)
    {
        head = true;
        for (int j = 0; j < candidate_count; j++)
        {
            //check if any of the rows contain true
            if (locked[j][i] == true)
            {
                //not head
                head = false;
                break;
            }
        }
        if (head == true)
            winner = i;
    }
    printf("%s\n", candidates[winner]);
    return;
}

