#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int only_digits(string);
void encipher(string, int);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    if (!only_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext: ");
    encipher(plaintext, key);
}

int only_digits(string str)
{
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        if (!isdigit(str[i]))
        {
            return 0;
        }
    }
    return 1;
}

void encipher(string str, int key)
{
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        if (isalpha(str[i]))
        {
            if (islower(str[i]))
            {
                str[i] = (str[i] - 'a' + key) % 26 + 'a';
            }
            else
            {
                str[i] = (str[i] - 'A' + key) % 26 + 'A';
            }
        }
    }
    printf("ciphertext: %s\n", str);
}