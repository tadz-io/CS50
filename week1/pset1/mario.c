/****************************************************************************
 * mario.c
 *
 * Minor Programmeren
 * Tadzio Holtrop
 *
 * Mario pyramid
 ***************************************************************************/


# include <stdio.h>
# include <cs50.h>

int main(void)
{
    int h;
    int i;
    int j;
    int hash;
    // check if input is valid: > 0 and < 24
    do
    {
        printf("height: ");
        h = GetInt();
    }
    while(h<0 || h>23);
    
    // rows
    for(i = 0; i < h; i++)
    {
        // columns for whitespaces
        for(j = h-i-1; j > 0; j--)
        {
            printf(" ");
        }
        // number of hashes per row
        for(hash = 0; hash < i+2; hash++)
        {
            printf("#");
        }
        // new row
        printf("\n");
    }
    
}