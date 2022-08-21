#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

bool only_digits(string digit);
string rotate(string plain_text, int key);

int main(int argc, string argv[])
{
    if (argc != 2 || only_digits(argv[1]) == 0) //checking if our key is digit-only
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        int key = atoi(argv[1]); //converting key to int
        string plain_text = get_string("plaintext: ");
        string ciphertext = rotate(plain_text, key); //calling the cipher
        printf("ciphertext: %s\n", ciphertext);
        return 0;
    }
}

bool only_digits(string digit)
{
    bool check = false;
    for (int i = 0; i < strlen(digit); i++)
    {
        if (isdigit(digit[i])) //checking each char for being a digit
        {
            check = true;
        }
        else
        {
            check = false;
        }
    }
    return check;
}

string rotate(string plain_text, int key)
{
    char p; //names based on a formula c = (p + k) % 26
    char c;
    for (int i = 0; i < strlen(plain_text); i++)
    {
        if (isalpha(plain_text[i])) //checking if a char is alphabetical
        {
            if (isupper(plain_text[i])) //checking if a char is uppercase
            {
                p = plain_text[i] - 'A';
                c = (p + key) % 26;
                plain_text[i] = c + 'A';
            }
            else if (islower(plain_text[i])) //checking if a char is lowercase
            {
                p = plain_text[i] - 'a';
                c = (p + key) % 26;
                plain_text[i] = c + 'a';
            }
        }
    }
    return plain_text;
}