#include <cs50.h>
#include <stdio.h>

void blocks(int k, int Block);

int main(void)
{
    int Height;
    do
    {
        Height = get_int("Height: ");
    }
    while (Height < 1 || Height > 8);

    int Block = 1;
    int Block1 = 1;
    int dot = Height;
    int j = 0;
    for (int i = 0; i < Height; i++)
    {
        for (int k = 1; k < dot; k++) //making space before blocks
        {
            printf(" ");
        }
        dot--;

        //for (int j = 0; j < Block; j++) //placing left blocks
        //{
        //    printf("#");
        //}
        //Block++;
        blocks(j, Block);

        printf("  ");

        for (int m = 0; m < Block1; m++) //placing right blocks
        {
            printf("#");
        }
        Block1++;

        printf("\n"); //next line
    }
}






void blocks(int j, int Block)
{
    for (int j = 0; j < Block; j++) //placing blocks
    {
        printf("#");
    }
    Block++;
}