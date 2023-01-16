#include <stdio.h>

int main(void)
{
    int height = 0;
    do
    {
        printf("Height: ");
        scanf("%i", &height);
    }
    while (height < 1 || height > 8);

    for (int i = 1; i <= height; i++)
    {
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}