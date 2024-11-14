#include "helpers.h"
#include <math.h>

int limitVal(int val);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int total = image[i][j].rgbtGreen + image[i][j].rgbtRed + image[i][j].rgbtBlue;
            int avg = (total + 1) / 3;

            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // GENERATING A COPY
    RGBTRIPLE imageCopy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i][j] = image[i][j];
        }
    }

    int rIndex = width - 1;

    // REPLACING EACH RGB IN REVERSE FROM COPY TO REAL IMG
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = imageCopy[i][rIndex];
            rIndex--;
        }
        rIndex = width - 1;
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE imageCopy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalRed = 0;
            int totalGreen = 0;
            int totalBlue = 0;
            int count = 0;

            // going through nearby pixels
            for (int p = -1; p <= 1; p++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int np = i + p;
                    int nl = j + l;

                    if (np >= 0 && np < height && nl >= 0 && nl < width)
                    {
                        totalRed += imageCopy[np][nl].rgbtRed;
                        totalGreen += imageCopy[np][nl].rgbtGreen;
                        totalBlue += imageCopy[np][nl].rgbtBlue;
                        count++;
                    }
                }
            }

            // adding 0.5 to fix any minor rounding issues
            image[i][j].rgbtRed = (int) ((totalRed / (float) count) + 0.5);
            image[i][j].rgbtGreen = (int) ((totalGreen / (float) count) + 0.5);
            image[i][j].rgbtBlue = (int) ((totalBlue / (float) count) + 0.5);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE imageCopy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i][j] = image[i][j];
        }
    }

    // starting both vals at 1 just to make sure it doesnt look through the edges of image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int redX = 0;
            int greenX = 0;
            int blueX = 0;
            int redY = 0;
            int greenY = 0;
            int blueY = 0;

            // looking through all nearby pixels
            for (int p = -1; p <= 1; p++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    int np = i + p;
                    int nl = j + l;

                    // applying sobel vals to all pixels and neighbours if within bounds
                    if (np >= 0 && np < height && nl >= 0 && nl < width)
                    {
                        redX += imageCopy[np][nl].rgbtRed * Gx[p + 1][l + 1];
                        greenX += imageCopy[np][nl].rgbtGreen * Gx[p + 1][l + 1];
                        blueX += imageCopy[np][nl].rgbtBlue * Gx[p + 1][l + 1];
                        redY += imageCopy[np][nl].rgbtRed * Gy[p + 1][l + 1];
                        greenY += imageCopy[np][nl].rgbtGreen * Gy[p + 1][l + 1];
                        blueY += imageCopy[np][nl].rgbtBlue * Gy[p + 1][l + 1];
                    }
                }
            }

            // adding 0.5 to final RGB to get past rounding issues
            int finalRed = (int) (sqrt(redX * redX + redY * redY) + 0.5);
            int finalGreen = (int) (sqrt(greenX * greenX + greenY * greenY) + 0.5);
            int finalBlue = (int) (sqrt(blueX * blueX + blueY * blueY) + 0.5);

            image[i][j].rgbtRed = limitVal(finalRed);
            image[i][j].rgbtGreen = limitVal(finalGreen);
            image[i][j].rgbtBlue = limitVal(finalBlue);
        }
    }

    return;
}

int limitVal(int val)
{
    if (val > 255)
    {
        return 255;
    }
    if (val < 0)
    {
        return 0;
    }
    return val;
}
