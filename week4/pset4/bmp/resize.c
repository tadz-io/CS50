/**
 * resize.c
 *
 * Tadzio Holtrop
 * 5670519
 * Minor Programmeren
 *
 * resizes bitmap image
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"

void updateHeader(BITMAPFILEHEADER *bf, BITMAPINFOHEADER *bi, int resize);
int pad(LONG width);

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }
   
    // resize
    int resize = atoi(argv[1]);
    
    if (resize < 0 || resize > 100)
    {
        printf("Invalid value for resize");
        return 4;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    // BITMAPFILEHEADER bfResize = bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    BITMAPINFOHEADER biResize = bi;


    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determine padding of original image
    int padOriginal =  pad(bi.biWidth);
    
    updateHeader(&bf, &biResize, resize);
   
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biResize, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < resize * biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
            // write RGBTRIPLE n times (resize) to output
            for (int k = 0; k < resize; k++)
            {
                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }

        }
        // return to beginning of scan line
        if ((i + 1) % resize != 0)
        {
            fseek(inptr, -bi.biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
        }
        // skip over padding in input file, if any
        else
        {
            fseek(inptr, padOriginal, SEEK_CUR);
        }

        // then add it back (to demonstrate how)
        for (int k = 0, padResize = pad(biResize.biWidth); k < padResize; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

/**
 * updateHeader updates bitmap header files when resizing image
 */
void updateHeader(BITMAPFILEHEADER *bf, BITMAPINFOHEADER *bi, int resize)
{
    // update BITMAPINFOHEADER
    bi->biWidth *= resize;
    bi->biHeight *= resize;
    bi->biSizeImage = (bi->biWidth) * abs(bi->biHeight) * 3 + pad(bi->biWidth) * abs(bi->biHeight);
    
    // update BITMALFILEHEADER
    bf->bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi->biSizeImage;
    
}

/**
 * function calculates padding needed for bitmap files of specified width
 */
int pad(LONG width)
{
    int pad =  (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;
    return pad;
}

