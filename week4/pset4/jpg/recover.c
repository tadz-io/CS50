/**
 * recover.c
 *
 * Tadzio Holtrop
 * 5670519
 * Minor Programmeren
 *
 * recovers jpg from raw file
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BUFSIZE 512
#define FILENAMESIZE 8

int main(int argc, char* argv[])
{
    const char* INFILE = "card.raw";
    
    FILE* inptr = fopen(INFILE, "r");
    FILE* outptr = NULL;
    
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", INFILE);
        return 2;
    }
    
    // make buffer of 512 bytes
    uint8_t buffer[BUFSIZE];
    bool jpgFound = false;
    
    int i = 0;
    char fileName[FILENAMESIZE];
    
    while (fread(buffer, BUFSIZE, 1, inptr) == 1)
    {
    
        if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) && 
            (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
           
            // close file
            if (jpgFound)
            {
                fclose(outptr);
            }
            else
            {
                jpgFound = true;
            }
           
            // create file
            sprintf(fileName, "%03i.jpg", i);
            outptr = fopen(fileName, "w");
            
            if (outptr == NULL)
            {
                fclose(inptr);
                printf("Could not create %s.\n", fileName);
                return 3;
            }
            
            i++;
       }
        
        // write to output
        if (jpgFound)
        {
            fwrite(buffer, BUFSIZE, 1, outptr);
        }
           
    }
    fclose(inptr);
    fclose(outptr);
    return 0;
}
