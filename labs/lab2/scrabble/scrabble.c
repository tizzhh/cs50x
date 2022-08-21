#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

char Alphabet[] = {97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score2 > score1)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)
{
    for (int i = 0; i < strlen(word); i++) //deleting non-alphabetical characters
    {
        if ((word[i] > 'z') || (word[i] < 'A') || (word[i] > 'Z' && word[i] < 'A'))
        {
            word[i] = '\0';
        }
    }
    int score = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        int j = 0;
        int k = -1;
        do
        {
            if (tolower(word[i]) == Alphabet[j]) //increasing score
            {
                score += POINTS[j];
            }
            k++;
            j++;
        }
        while (tolower(word[i]) != Alphabet [k]);
    }
    return score;
}

//I could've just used "islower" and "isupper" with ifs 