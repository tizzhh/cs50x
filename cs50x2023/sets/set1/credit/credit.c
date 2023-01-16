#include <cs50.h>
#include <stdio.h>

int get_length(long);
int verify(long);
char start(int, long);

int main(void)
{
    long num = get_long("Number: ");
    int length = get_length(num);
    int check = verify(num);
    if (!check || length < 13)
    {
        printf("INVALID\n");
        return 0;
    }
    char card = start(length, num);
    switch (card)
    {
        case 'v':
            printf("VISA\n");
            break;
        case 'm':
            printf("MASTERCARD\n");
            break;
        case 'a':
            printf("AMEX\n");
            break;
        case 'i':
            printf("INVALID\n");M
            break;
    }
}

int get_length(long num)
{
    int len = 0;
    for (long i = num; i != 0; i /= 10)
    {
        len++;
    }
    return len;
}

int verify(long num)
{
    long sum1 = 0, sum2 = 0;
    for (long i = num / 10; i != 0; i /= 100)
    {
        if ((i % 10) * 2 >= 10)
        {
            sum1 += ((i % 10) * 2) % 10 + ((i % 10) * 2) / 10;
        }
        else
        {
            sum1 += i % 10 * 2;
        }
    }
    for (long i = num; i != 0; i /= 100)
    {
        sum2 += i % 10;
    }
    return (sum1 + sum2) % 10 == 0 ? 1 : 0;
}

char start(int len, long num)
{
    long startv = num / 100000000000000;
    long starta = num / 10000000000000;
    if (num / 1000000000000 == 4 && len == 13)
    {
        return 'v';
    }
    else if (startv / 10 == 4 && len == 16)
    {
        return 'v';
    }
    else if ((startv == 51 || startv == 52 || startv == 53\
              || startv == 54 || startv == 55) && len == 16)
    {
        return 'm';
    }
    else if ((starta == 37 || starta == 37) && len == 15)
    {
        return 'a';
    }
    else
    {
        return 'i';
    }
    return 0;
}