#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_alpha(string);
int check_unique(string);
void encipher(string, string);

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    if (!check_alpha(argv[1]))
    {
        return 1;
    }
    if (!check_unique(argv[1]))
    {
        printf("Key must not contain repeated characters.\n");
        return 1;
    }
    string text = get_string("plaintext: ");
    encipher(text, argv[1]);
}

int check_alpha(string str)
{
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        if (!isalpha(str[i]))
        {
            printf("Key must only contain alphabetic characters.\n");
            return 0;
        }
    }
    return 1;
}

int check_unique(string str)
{
    char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', \
                       'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', \
                       'q', 'r', 's', 't', 'u', 'v', 'w', 'x', \
                       'y', 'z'
                      };

    int check = 0;
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        check = 0;
        for (int j = 0; j < 26; j++)
        {
            if (tolower(str[i]) == alphabet[j])
            {
                alphabet[j] = '0';
                check = 1;
            }
        }
        if (!check)
        {
            return 0;
        }
    }
    return 1;
}

void encipher(string text, string key)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (islower(text[i]))
        {
            text[i] = toupper(key[text[i] - 'a']) + 32;
        }
        else if (isupper(text[i]))
        {
            text[i] = toupper(key[text[i] - 'A']);
        }
    }
    printf("ciphertext: %s\n", text);
}
