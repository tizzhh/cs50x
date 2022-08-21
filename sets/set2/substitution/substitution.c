#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool alphabet(string long_key);
string rotate(string plain_text, string long_key);
bool repeated_characters(string long_key);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters\n");
        return 1;
    }
    else if (alphabet(argv[1]) == 0)
    {
        printf("Key must only contain alphabetic characters\n");
        return 1;
    }
    else if (repeated_characters(argv[1]) == 0)
    {
        printf("Key must not contain repeated characters\n");
        return 1;
    }
    else
    {
        string plain_text = get_string("plaintext: ");
        string ciphertext = rotate(plain_text, argv[1]); //calling the cipher
        printf("ciphertext: %s\n", ciphertext);
        return 0;
    }
}

bool alphabet(string long_key)
{
    bool check = false;
    for (int i = 0; i < strlen(long_key); i++)
    {
        if (isalpha(long_key[i])) //cheching if each char is from alphabet
        {
            check = true;
        }
        else
        {
            check = false;
            break;
        }
    }
    return check;
}

bool repeated_characters(string long_key)
{
    bool check = true;
    for (int i = 0; i < strlen(long_key) - 1; i++)
    {
        for (int j = 1; j < strlen(long_key); j++)
        {
            if (long_key[i] == long_key[j])
            {
                if (i != j)
                {
                    check = false;
                }
            }
        }
    }
    return check;
}

string rotate(string plain_text, string long_key)
{
    int a;
    for (int i = 0; i < strlen(plain_text); i++)
    {
        if (isalpha(plain_text[i])) //checking if a char is alphabetical
        {
            if (isupper(plain_text[i])) //checking if a char is uppercase
            {
                a = plain_text[i] - 'A';
                plain_text[i] = toupper(long_key[a]);
            }
            else if (islower(plain_text[i])) //checking if a char is lowercase
            {
                a = plain_text[i] - 'a';
                plain_text[i] = tolower(long_key[a]);
            }
        }
    }
    return plain_text;
}