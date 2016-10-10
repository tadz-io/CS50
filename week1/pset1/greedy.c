/****************************************************************************
 * greedy.c
 *
 * Tadzio Holtrop
 * Minor Programmeren
 * Greedy
 *
 * Calculates minimum number of coins needed for change
 ***************************************************************************/

# include <stdio.h>
# include <cs50.h>
# include <math.h>

int main(void)
{
    float n = 0;
    long cents = 0;
    long quarters = 0;
    long dimes = 0;
    long nickels = 0;
    long pennies = 0;
    
    // check for invalid input
    do
    {
        printf("How much change is owed?\n");
        n = GetFloat();    
    }
    while(n<0);
    
    // convert change to cents
    cents = (long) roundf(n*100);
    //printf("amount in cents: %ld\n", cents);
    // quarters
    quarters = (cents-(cents%25))/25;
    cents = cents%25;
    // dimes
    dimes = (cents-(cents%10))/10;
    cents = cents%10;
    // nickels
    nickels = (cents-(cents%5))/5;
    cents = cents%5;
    // pennies
    pennies = cents;
    /*
    printf("number of quarters: %ld\n", quarters);
    printf("number of dimes: %ld\n", dimes);
    printf("number of nickels: %ld\n", nickels);
    printf("number of pennies: %ld\n", pennies);
    */
    
    printf("%ld\n", quarters+dimes+nickels+pennies);   
    
}