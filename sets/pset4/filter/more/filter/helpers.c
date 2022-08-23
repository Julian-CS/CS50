#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int pixel;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            pixel = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed)/3.0);
            image[i][j].rgbtBlue = pixel;
            image[i][j].rgbtGreen = pixel;
            image[i][j].rgbtRed = pixel;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed, sepiaGreen, sepiaBlue;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {

            sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            if(sepiaRed > 255)
                sepiaRed = 255;
            if(sepiaGreen > 255)
                sepiaGreen = 255;
            if(sepiaBlue > 255)
                sepiaBlue = 255;

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer;
    int half = width/2;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < half; j++)
        {
           buffer = image[i][j];
           image[i][j] = image[i][width-1-j];
           image[i][width-1-j] = buffer;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int buffRed[height][width];
    int buffBlue[height][width];
    int buffGreen[height][width];

    //GO THROUGH EVERY PIXEL
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {

            //SUMS AND COUNTERS FOR THIS PIXEL [i][j]
            float counter = 0.0;
            int sumRed = 0;
            int sumBlue = 0;
            int sumGreen = 0;

            //Loops to go through every pixel adjacent to current pixel [i][j]
            for(int p = 0; p < 3; p++)
            {
                for(int s = 0; s < 3; s++)
                {
                    //Check if pixels are adjacent inside the image or not..
                    if(((i+1-p) >= 0) && ((i+1-p) < height) && ((j+1-s) >= 0) && ((j+1-s) < width))
                    {
                        sumRed += image[i+1-p][j+1-s].rgbtRed;
                        sumBlue += image[i+1-p][j+1-s].rgbtBlue;
                        sumGreen += image[i+1-p][j+1-s].rgbtGreen;

                        //count valid pixels
                        counter++;
                    }

                }
            }
            buffRed[i][j] = round(sumRed / counter);
            buffBlue[i][j] = round(sumBlue / counter);
            buffGreen[i][j] = round(sumGreen / counter);
        }
    }




    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = buffBlue[i][j];
            image[i][j].rgbtGreen = buffGreen[i][j];
            image[i][j].rgbtRed = buffRed[i][j];
        }
    }

    return;
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    //clone
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }



    //GO THROUGH EVERY PIXEL
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {

            //SUMS AND COUNTERS FOR THIS PIXEL [i][j]
            float counter = 0.0;
            long sumRedx = 0;
            long sumBluex = 0;
            long sumGreenx = 0;

            long sumRedy = 0;
            long sumBluey = 0;
            long sumGreeny = 0;

            //Populate Gx and Gy
            long Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
            long Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};


            //Loops to go through every pixel adjacent to current pixel [i][j]
            for(int p = 0; p < 3; p++)
            {
                for(int s = 0; s < 3; s++)
                {
                    //Check if pixels are adjacent inside the image or not..
                    if(((i+1-p) >= 0) && ((i+1-p) < height) && ((j+1-s) >= 0) && ((j+1-s) < width))
                    {
                        sumRedx += (Gx[p][s] * image[i-1+p][j-1+s].rgbtRed);
                        sumRedy += (Gy[p][s] * image[i-1+p][j-1+s].rgbtRed);

                        sumBluex += (Gx[p][s] * image[i-1+p][j-1+s].rgbtBlue);
                        sumBluey += (Gy[p][s] * image[i-1+p][j-1+s].rgbtBlue);

                        sumGreenx += (Gx[p][s] * image[i-1+p][j-1+s].rgbtGreen);
                        sumGreeny += (Gy[p][s] * image[i-1+p][j-1+s].rgbtGreen);
                    }

                }
            }

        //calculate red green and blue values for copy
        int red = round(fmin(255,sqrt((sumRedx*sumRedx) + (sumRedy*sumRedy))));
        int blue = round(fmin(255,sqrt((sumBluex*sumBluex) + (sumBluey*sumBluey))));
        int green = round(fmin(255,sqrt((sumGreenx*sumGreenx) + (sumGreeny*sumGreeny))));

        //apply changes to the copy of the image
        copy[i][j].rgbtRed = red;
        copy[i][j].rgbtGreen = green;
        copy[i][j].rgbtBlue = blue;
        }
    }

    //Clone back
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = copy[i][j];
        }
    }

    return;
}
