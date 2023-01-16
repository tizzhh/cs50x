#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    int byte[BITS_IN_BYTE];
    int pos;
    string text = get_string("Message: ");
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            byte[j] = 0;
        }
        pos = 7;
        for (int j = text[i]; j != 0; j /= 2)
        {
            byte[pos] = j % 2;
            pos--;
        }
        for (int j = 0; j < 8; j++)
        {
            print_bulb(byte[j]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
