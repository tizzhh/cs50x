#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int BLOCK_SIZE = 512;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }


    BYTE buffer[BLOCK_SIZE];
    int count = 0;
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        return 1;
    }

    int check = 0;
    char filename[8];

    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            sprintf(filename, "%03i.jpg", count);
            FILE *img = fopen(filename, "w");
            if (img == NULL)
            {
                return 1;
            }
            fwrite(buffer, BLOCK_SIZE, 1, img);
            fclose(img);
            count++;
            check = 1;
        }
        else if (check)
        {
            FILE *img = fopen(filename, "a");
            if (img == NULL)
            {
                return 1;
            }
            fwrite(buffer, BLOCK_SIZE, 1, img);
            fclose(img);
        }
    }
    fclose(file);
}