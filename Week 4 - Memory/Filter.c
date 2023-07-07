//FILTER

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

int main(int argc, char *argv[])
{
    // Define allowable filters
    char *filters = "bgrs";

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

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 4;
    }

    // Open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 5;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 6;
    }

    // Get image's dimensions
    int height = abs(bi.biHeight);
    int width = bi.biWidth;

    // Allocate memory for image
    RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        printf("Not enough memory to store image.\n");
        fclose(outptr);
        fclose(inptr);
        return 7;
    }

    // Determine padding for scanlines
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    // Iterate over infile's scanlines
    for (int i = 0; i < height; i++)
    {
        // Read row into pixel array
        fread(image[i], sizeof(RGBTRIPLE), width, inptr);

        // Skip over padding
        fseek(inptr, padding, SEEK_CUR);
    }

    // Filter image
    switch (filter)
    {
        // Blur
        case 'b':
            blur(height, width, image);
            break;

        // Grayscale
        case 'g':
            grayscale(height, width, image);
            break;

        // Reflection
        case 'r':
            reflect(height, width, image);
            break;

        // Sepia
        case 's':
            sepia(height, width, image);
            break;
    }

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Write new pixels to outfile
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
    return 0;
}

//HELPERS

#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
      {
        float sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
        float average = sum / 3.0;
        int roundedAverage = (int)round(average);


        image[i][j].rgbtBlue = roundedAverage;
        image[i][j].rgbtGreen = roundedAverage;
        image[i][j].rgbtRed = roundedAverage;
      }

    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width; j++)
      {

      int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
      int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
      int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);

      sepiaBlue = (int)fmin(sepiaBlue, 255);
      sepiaGreen = (int)fmin(sepiaGreen, 255);
      sepiaRed = (int)fmin(sepiaRed, 255);

      image[i][j].rgbtBlue = round(sepiaBlue);
      image[i][j].rgbtGreen = round(sepiaGreen);
      image[i][j].rgbtRed = round(sepiaRed);

      }

    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
  RGBTRIPLE temp[height][width];

   for (int i = 0; i < height; i++)
    {
      for (int j = 0; j < width / 2; j++)
      {
       temp[i][j] = image[i][j];
       image [i][j] = image[i][width - 1 - j];
       image[i][width - 1 - j] = temp[i][j];
      }

    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

   RGBTRIPLE copy[height][width];

   //copy image
   for (int i = 0; i < height; i++)
   {
     for (int j = 0; j < width; j++)
     {
      copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
      copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
      copy[i][j].rgbtRed = image[i][j].rgbtRed;
      }
    }

    //apply blur effect
     for (int i = 0; i < height; i++)
   {
       for (int j = 0; j < width; j++)
       {
        int count = 0;
        int averageBlue = 0;
        int averageGreen = 0;
        int averageRed = 0;


          for (int q = i - 1; q <= i + 1; q++)
          {
            for (int s = j - 1; s <= j + 1; s++)
            {
              if (q >= 0 && q <= height - 1 && s >= 0 && s <= width - 1)
              {
                averageBlue += copy[q][s].rgbtBlue;
                averageGreen += copy[q][s].rgbtGreen;
                averageRed += copy[q][s].rgbtRed;
                count++;
              }

             }

      image[i][j].rgbtBlue = (int)round((double)averageBlue / (double)count);
      image[i][j].rgbtGreen = (int)round((double)averageGreen / (double)count);
      image[i][j].rgbtRed = (int)round((double)averageRed / (double)count);

          }

       }
   }

    return;
}



