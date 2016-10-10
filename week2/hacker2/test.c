# include <stdio.h>
# include <cs50.h>
# include <string.h>

int main(void)
{
    int remain;
    int number = 8;
    int j = 0;
    // fill char array with null terminators so strlen() can count number of inserted chars
    char base_conv[3] = {1};
    
    while(number>0)
    {
        // calculate remainder
        remain = number%7;
        base_conv[j] = remain;
        //printf("length: %lu\n", strlen(base_conv));
        printf("%c", base_conv[j]);
        // divide by base
        number = number/7;
        
        j++;
    }
    
    printf("\tlength: %lu\n", strlen(base_conv));
    return 0;
}