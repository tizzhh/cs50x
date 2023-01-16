#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int av;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            av = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = av;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int b, g, r;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            b = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            g = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            r = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            image[i][j].rgbtBlue = b > 255 ? 255 : b;
            image[i][j].rgbtGreen = g > 255 ? 255 : g;
            image[i][j].rgbtRed = r > 255 ? 255 : r;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, n = width / 2; j < n; j++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    int avb, avg, avr, count;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            count = avb = avg = avr = 0;
            for (int k = i - 1; k < i + 2; k++)
            {
                for (int l = j - 1; l < j + 2; l++)
                {
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        avb += copy[k][l].rgbtBlue;
                        avg += copy[k][l].rgbtGreen;
                        avr += copy[k][l].rgbtRed;
                        count++;
                    }
                }
            }
            image[i][j].rgbtBlue = round(avb / (float) count);
            image[i][j].rgbtGreen = round(avg / (float) count);
            image[i][j].rgbtRed = round(avr / (float) count);
        }
    }
    return;
}
