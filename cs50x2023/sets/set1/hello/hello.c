#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char name[100];
    printf("What's your name?\n");
    scanf("%s", name);
    printf("hello, %s\n", name);
}