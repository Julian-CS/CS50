// Implements a dictionary's functionality
//intialize all pointers to null todo
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
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
const unsigned int N = 50000;


// Hash table
node *table[N];

int count_words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //+1?
    int n = strlen(word);
    char copy[n+1];
    copy[n] = '\0';
    for (int i = 0; i < n; i++)
    {
        copy[i] = tolower(word[i]);
    }



    int index = hash(copy);
    node *cursor = table[index];

    while(cursor != NULL)
    {
        if(strcasecmp(cursor->word, copy) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
/*Adapted by Neel Mehta from
http://stackoverflow.com/questions/2571683/djb2-hash-function.*/

    unsigned long hash = 5381;

    for (const char* ptr = word; *ptr != '\0'; ptr++)
    {
        hash = ((hash << 5) + hash) + tolower(*ptr);
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //open file
    FILE *dict = fopen(dictionary, "r");
    if(dict == NULL)
        return false;


    //intizialize table
    for(int i = 0; i < N; i++)
        table[i] = NULL;

    char word[LENGTH +1];
    
    //store word in hash table
    while(fscanf(dict, "%s", word) != EOF)
    {
        count_words++;
        node *tmp = malloc(sizeof(node));
        if(tmp == NULL)
        {
            fclose(dict);
            return false;
        }

        strcpy(tmp->word, word);
        tmp->next = NULL;
        int index = hash(word);


        tmp->next = table[index];
        table[index] = tmp;


    }
    fclose(dict);
    return true;
}




// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return count_words;
}


// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{

    for (int i = 0; i< N; i++)
    {
        node *uncursor = table[i];
        while(uncursor != NULL)
        {
            node *tmp = uncursor;
            uncursor = uncursor->next;
            free(tmp);
        }
    }
    return true;
}
