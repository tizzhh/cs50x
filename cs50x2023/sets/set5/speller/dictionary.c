// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
//const unsigned int N = 26;
const unsigned int N = 676;

// Hash table
node *table[N];

// Counting number of words in dictionary
int count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    node *cursor = table[hash(word)];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
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
    // TODO: Improve this hash function
    return (toupper(word[0]) - 'A') * 26 + ((word[1] == '\0') ? 0 : toupper(word[1]) - 'A');
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    char word_dict[LENGTH + 1];
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }
    unsigned int pos = 0;
    while (fscanf(dict, "%s", word_dict) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, word_dict);
        count++;
        pos = hash(n->word);
        n->next = table[pos];
        table[pos] = n;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor->next;
            free(cursor);
            cursor = tmp;
        }
    }
    return true;
}
