#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Number: ");
    long num0 = number;
    int length = 0;
    while (num0 > 0) //counting the length of our card number
    {
        length += 1;
        num0 /= 10;
    }

    long num1 = number;
    int summ1 = 0;
    int summ2 = 0;
    int i = 0;
    int x = 0;
    while (num1 > 0) //summ of digits that are to be multiplied
    {
        if (i % 2 == 0)
        {
            x = num1 / 10 % 10 * 2;
            if (x > 9) //checking if a digit became greater than 10 after multiplication
            {
                summ1 += x / 10 + x % 10;
            }
            else
            {
                summ1 += x;
            }
        }
        num1 /= 10;
        i++;
    }

    long num2 = number;
    int j = 1;
    while (num2 > 0) //summ of digits that weren't multiplied
    {
        if (j % 2 != 0)
        {
            summ2 += num2 % 10;
        }
        num2 /= 10;
        j++;
    }

    int ftd = number / 100000000000000; //first two digits for mastercard
    int ftd1 = number / 10000000000000; //first two digits for amex
    if ((summ1 + summ2) % 10 == 0)
    {
        if ((length == 16) && (ftd == 51 || ftd == 52 || ftd == 53 || ftd == 54 || ftd == 55))
        {
            printf("MASTERCARD\n");
        }
        else if ((length == 15) && (ftd1 == 34 || ftd1 == 37))
        {
            printf("AMEX\n");
        }
        else if ((length == 13 || length == 16) && (number / 1000000000000000 == 4 || number / 1000000000000 == 4))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
