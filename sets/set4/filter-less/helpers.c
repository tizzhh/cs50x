#include "helpers.h"
#include <math.h>

void pixel_check(int height, int width, int x, int y, float *avred, float *avgreen, float *avblue, RGBTRIPLE copy[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float av = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            av = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            av = (int) round(av);
            image[i][j].rgbtRed = av;
            image[i][j].rgbtGreen = av;
            image[i][j].rgbtBlue = av;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    float sepiaRed = 0;
    float sepiaGreen = 0;
    float sepiaBlue = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            sepiaRed = (int) round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            sepiaGreen = (int) round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            sepiaBlue = (int) round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int p1 = 0;
    int p2 = 0;
    int p3 = 0;
    int mid = width / 2;
    int plwidth = width - 1;
    for (int i = 0; i < height; i++)
    {
        plwidth = width - 1;
        for (int j = 0; j != mid; j++)
        {
            p1 = image[i][j].rgbtRed;
            p2 = image[i][j].rgbtGreen;
            p3 = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][plwidth].rgbtRed;
            image[i][j].rgbtGreen = image[i][plwidth].rgbtGreen;
            image[i][j].rgbtBlue = image[i][plwidth].rgbtBlue;
            image[i][plwidth].rgbtRed = p1;
            image[i][plwidth].rgbtGreen = p2;
            image[i][plwidth].rgbtBlue = p3;
            plwidth--;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width]; //making a copy of an image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float avred = 0; //making 3 variables for each pixel
            float avgreen = 0;
            float avblue = 0;
            pixel_check(height, width, i, j, &avred, &avgreen, &avblue, copy);
            avred = round(avred);
            avgreen = round(avgreen);
            avblue = round(avblue);
            image[i][j].rgbtRed = avred;
            image[i][j].rgbtGreen = avgreen;
            image[i][j].rgbtBlue = avblue;
        }
    }
    return;
}

void pixel_check(int height, int width, int x, int y, float *avred, float *avgreen, float *avblue, RGBTRIPLE copy[height][width])
{
    float count = 0.0;
    for (int i = x - 1; i <= x + 1; i++) //checking if there are pixels around our pixel
    {
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (i >= 0 && i < height && j >= 0 && j < width) //if there are, we summ the values of rgb
            {
                *avred += copy[i][j].rgbtRed;
                *avgreen += copy[i][j].rgbtGreen;
                *avblue += copy[i][j].rgbtBlue;
                count ++;
            }
        }
    }
    *avred /= count;
    *avgreen /= count;
    *avblue /= count;
    return;
}
