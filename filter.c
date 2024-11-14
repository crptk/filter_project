#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

// Function to process 24-bit BMP images
int main(int argc, char *argv[])
{
    // Define allowable filters
    char *filters = "begr";

    // Get filter flag and check validity
    char filter = getopt(argc, argv, filters);
    if (filter == '?')
    {
        printf("Invalid filter.\n");
        return 1;
    }

    // Ensure only one filter
    if (getopt(argc, argv, filters) != -1)
    {
        printf("Only one filter allowed.\n");
        return 2;
    }

    // Ensure proper usage
    if (argc != optind + 2)
    {
        printf("Usage: ./filter [flag] infile outfile\n");
        return 3;
    }

    // Remember filenames
    char *infile = argv[optind];
    char *outfile = argv[optind + 1];

    // Open input file in binary mode
    FILE *inptr = fopen(infile, "rb");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 4;
    }

    // Open output file in binary mode
    FILE *outptr = fopen(outfile, "wb");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 5;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    if (fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr) != 1)
    {
        printf("Failed to read BITMAPFILEHEADER\n");
        fclose(inptr);
        fclose(outptr);
        return 6;
    }

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    if (fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr) != 1)
    {
        printf("Failed to read BITMAPINFOHEADER\n");
        fclose(inptr);
        fclose(outptr);
        return 7;
    }

    // Debugging print statements for header fields
    // printf("Debug Information:\n");
    // printf("bfType: 0x%x\n", bf.bfType);           // Should be 0x4D42 for BMP files
    // printf("biBitCount: %u\n", bi.biBitCount);      // Should be 24 for 24-bit BMP
    // printf("biCompression: %u\n", bi.biCompression); // Should be 0 for uncompressed BMP

    // Ensure infile is a 24-bit uncompressed BMP
    if (bf.bfType != 0x4D42 || bi.biBitCount != 24 || bi.biCompression != 0)
    {
        printf("Unsupported file format: must be a 24-bit uncompressed BMP.\n");
        fclose(outptr);
        fclose(inptr);
        return 8;
    }

    // Get image dimensions
    int height = abs(bi.biHeight);
    int width = bi.biWidth;

    // Allocate memory for image
    RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        printf("Not enough memory to store image.\n");
        fclose(outptr);
        fclose(inptr);
        return 9;
    }

    // Determine padding for scanlines
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    // Read the image into memory
    for (int i = 0; i < height; i++)
    {
        // Read row into pixel array
        if (fread(image[i], sizeof(RGBTRIPLE), width, inptr) != width)
        {
            printf("Error reading scanline\n");
            free(image);
            fclose(outptr);
            fclose(inptr);
            return 10;
        }

        // Skip over padding
        fseek(inptr, padding, SEEK_CUR);
    }

    // Apply the chosen filter
    switch (filter)
    {
        case 'b':
            blur(height, width, image);
            break;
        case 'e':
            edges(height, width, image);
            break;
        case 'g':
            grayscale(height, width, image);
            break;
        case 'r':
            reflect(height, width, image);
            break;
    }

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Write the modified pixels to the output file
    for (int i = 0; i < height; i++)
    {
        // Write row to outfile
        fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);

        // Write padding at end of row
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // Free memory for image
    free(image);

    // Close files
    fclose(inptr);
    fclose(outptr);
    printf("Operation successful.");
    return 0;
}
