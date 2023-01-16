#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start = 0, end = 0, years = 0;
    do
    {
        printf("Start size: ");
        scanf("%i", &start);
    }
    while (start < 9);
    // TODO: Prompt for end size
    do
    {
        printf("End size: ");
        scanf("%i", &end);
    }
    while (end < start);
    // TODO: Calculate number of years until we reach threshold
    while (start < end)
    {
        start += (start / 3) - (start / 4);
        years++;
    }
    // TODO: Print number of years
    printf("Years: %i\n", years);
}
