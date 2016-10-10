/****************************************************************************
 * initials.c - hackers pset
 * 
 * Tadzio Holtrop
 * 5670519
 * Minor Programmeren
 *
 * gets initials from string and capatalizes initials
 ***************************************************************************/

# include <stdio.h>
# include <cs50.h>
# include <ctype.h>
# include <string.h>

int main(void)
{
    string name;

    // get input
    name = GetString();
    
    if (!isspace(name[0]))
    {
        printf("%c", toupper(name[0]));
    }

    for (int i = 0, n = strlen(name)-1; i < n; i++)
    {
        if (isspace(name[i]) && isalpha(name[i+1]))
        {
            printf("%c", toupper(name[i+1]));
        }
    }
    printf("\n");
    return(0);
}