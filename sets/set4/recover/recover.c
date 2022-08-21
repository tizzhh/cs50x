#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

const int BLOCK_SIZE = 512;


int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    int count = 0;
    BYTE bytes[BLOCK_SIZE];

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        return 1;
    }

    int found = 0;
    char *filename = malloc(8);

    while (fread(bytes, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            found = 1;
            sprintf(filename, "%03i.jpg", count);
            FILE *img = fopen(filename, "w");
            fwrite(bytes, 1, BLOCK_SIZE, img);
            fclose(img);
            count++;
        }
        else if (found)
        {
            FILE *img = fopen(filename, "a");
            fwrite(bytes, 1, BLOCK_SIZE, img);
            fclose(img);
        }
    }
    free(filename);
    fclose(file);
    return 0;
}