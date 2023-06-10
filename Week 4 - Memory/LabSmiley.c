#include "helpers.h"

//rgbtBlue = 129
//rgbtGreen = 175
//rgbtRed = 62

void colorize(int height, int width, RGBTRIPLE image[height][width])
{

for (int i = 0; i < height; i++)
{
  for (int j = 0; j < width; j++)
  {

    if (image[i][j].rgbtBlue == 0 && image[i][j].rgbtGreen == 0 && image[i][j].rgbtRed == 0)
    {
    image[i][j].rgbtBlue = 129;
    image[i][j].rgbtGreen = 175;
    image[i][j].rgbtRed = 62;
    }

  }

}

}
