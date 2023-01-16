#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    int pos = 0;
    char format[10];
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (argv[1][i] == '.')
        {
            pos = i;
            break;
        }
    }

    for (int i = pos, n = strlen(argv[1]), j = 0; i < n; i++)
    {
        format[j] = argv[1][i];
        j++;
    }

    if (!pos || strcmp(format, ".wav") != 0)
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        return 1;
    }

    // Read header into an array
    // TODO #3
    WAVHEADER header;
    fread(&header, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    int if_wav = check_format(header);

    // Open output file for writing
    // TODO #5
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        return 1;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);

    // Write reversed audio to file
    // TODO #8
    fseek(input, -block_size, SEEK_END);
    BYTE block[block_size];
    while (ftell(input) >= sizeof(WAVHEADER))
    {
        fread(block, block_size, 1, input);
        fwrite(block, block_size, 1, output);
        fseek(input, -2 * block_size, SEEK_CUR);
    }
    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header)
{
    // TODO #4
    if (strncmp((char *) header.format, "WAVE", 4) == 0)
    {
        return 1;
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    return header.numChannels * (header.bitsPerSample / 8);
}