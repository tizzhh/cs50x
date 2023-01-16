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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int gxb, gxg, gxr, gyb, gyg, gyr, newblue, newgreen, newred, newi, newj;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            gxb = gxg = gxr = gyb = gyg = gyr = newi = 0;
            for (int k = i - 1; k < i + 2; k++)
            {
                newj = 0;
                for (int l = j - 1; l < j + 2; l++)
                {
                    if ((k >= 0 && k < height) && (l >= 0 && l < width))
                    {
                        gxb += gx[newi][newj] * copy[k][l].rgbtBlue;
                        gxg += gx[newi][newj] * copy[k][l].rgbtGreen;
                        gxr += gx[newi][newj] * copy[k][l].rgbtRed;
                        gyb += gy[newi][newj] * copy[k][l].rgbtBlue;
                        gyg += gy[newi][newj] * copy[k][l].rgbtGreen;
                        gyr += gy[newi][newj] * copy[k][l].rgbtRed;
                    }
                    newj++;
                }
                newi++;
            }
            newblue = round(sqrt(pow(gxb, 2) + pow(gyb, 2)));
            newgreen = round(sqrt(pow(gxg, 2) + pow(gyg, 2)));
            newred = round(sqrt(pow(gxr, 2) + pow(gyr, 2)));
            image[i][j].rgbtBlue = newblue > 255 ? 255 : newblue;
            image[i][j].rgbtGreen = newgreen > 255 ? 255 : newgreen;
            image[i][j].rgbtRed = newred > 255 ? 255 : newred;
        }
    }
    return;
}
