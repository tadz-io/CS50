/****************************************************************************
 * water.c
 *
 * Minor Programmeren
 * Tadzio Holtrop
 *
 * Calculates number of water bottles used when showering
 ***************************************************************************/

# include <stdio.h>
# include <cs50.h>

int main(void)
{
    int time;
    int n;
    
    printf("minutes: ");
    time = GetInt();
    n = time*12;
    printf("bottles: %d", n);
}