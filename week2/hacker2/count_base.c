# include <stdio.h>
# include <cs50.h>
# include <string.h>

void rev(char base[]);

int main(void)
{
    int remain;
    int number;
    // fill char array with null terminators so strlen() can count number of inserted chars
    char base_conv[5] = {"\0"};
    
    for(int i = 1; i < 50; i++)
    {
        int j = 0;
        number = i;
        
        printf("number: %i \tbase: ", number);
        
        // convert number to different base
        while(number > 0)
        {
            number--;
            // calculate remainder of number
            remain = number%26;
            // convert remainder number to respective printable character
            base_conv[j] = remain + 65;
            printf("%c", base_conv[j]);
            // divide number by base
            number = number/26;
            j++;
        }
        
        
        printf("\t");
        rev(base_conv);
        printf("\n");
        // still have to reset
    } 
    
    return 0;
}

void rev(char base[])
{
    char baseN[strlen(base)];
    
    for(int i = strlen(base)-1, j = 0; i>=0; i--, j++)
    {
        baseN[j] = base[i];
    }
    printf("\toutput: %s", baseN);
}