#include "helpers.h"
#include <math.h>
#include <stdio.h>

void pixel_check(int height, int width, int x, int y, float *avred, float *avgreen, float *avblue, RGBTRIPLE copy[height][width]);
void pixel_check_edge(int height, int width, int x, int y, int *avred1, int *avgreen1, int *avblue1, int *avred2, int *avgreen2,
                      int *avblue2, RGBTRIPLE copy[height][width], int gx[3][3], int gy[3][3]);

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

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

    int newred = 0;
    int newgreen = 0;
    int newblue = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avred1 = 0;
            int avgreen1 = 0;
            int avblue1 = 0;
            int avred2 = 0;
            int avgreen2 = 0;
            int avblue2 = 0;
            pixel_check_edge(height, width, i, j, &avred1, &avgreen1, &avblue1, &avred2, &avgreen2, &avblue2, copy, gx, gy);
            newred = round(sqrt(pow(avred1, 2) + pow(avred2, 2)));
            if (newred  > 255)
            {
                newred = 255;
            }
            newgreen = round(sqrt(pow(avgreen1, 2) + pow(avgreen2, 2)));
            if (newgreen  > 255)
            {
                newgreen = 255;
            }
            newblue = round(sqrt(pow(avblue1, 2) + pow(avblue2, 2)));
            if (newblue  > 255)
            {
                newblue = 255;
            }
            image[i][j].rgbtRed = newred;
            image[i][j].rgbtGreen = newgreen;
            image[i][j].rgbtBlue = newblue;
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

void pixel_check_edge(int height, int width, int x, int y, int *avred1, int *avgreen1, int *avblue1, int *avred2, int *avgreen2,
                      int *avblue2, RGBTRIPLE copy[height][width], int gx[3][3], int gy[3][3])
{
    int k = 0;
    for (int i = x - 1; i <= x + 1; i++) //checking if there are pixels around our pixel
    {
        int k1 = 0;
        for (int j = y - 1; j <= y + 1; j++)
        {
            if (i >= 0 && i < height && j >= 0 && j < width) //if there are, we calculate gx and gy
            {
                *avred1 += copy[i][j].rgbtRed * gx[k][k1];
                *avgreen1 += copy[i][j].rgbtGreen * gx[k][k1];
                *avblue1 += copy[i][j].rgbtBlue * gx[k][k1];
                *avred2 += copy[i][j].rgbtRed * gy[k][k1];
                *avgreen2 += copy[i][j].rgbtGreen * gy[k][k1];
                *avblue2 += copy[i][j].rgbtBlue * gy[k][k1];
            }
            else
            {
                *avred1 += 0 * gx[k][k1];
                *avgreen1 += 0 * gx[k][k1];
                *avblue1 += 0 * gx[k][k1];
                *avred2 += 0 * gy[k][k1];
                *avgreen2 += 0 * gy[k][k1];
                *avblue2 += 0 * gy[k][k1];
            }
            k1++;
        }
        k++;
    }
    return;
}