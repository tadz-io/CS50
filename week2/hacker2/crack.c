/****************************************************************************
 * crack.c
 *
 * Tadzio Holtrop
 * 5670519
 * Minor Programmeren
 *
 * crack.c tries to crack a password of max 8 characters using brute force
 * the password is encoded with a DES algorithm
 * 
 * All possible combinations are tried by counting in base 95 through all
 * printable ASCII characters
 ***************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <crypt.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#define _XOPEN_SOURCE

// prototype
void baseConv(char * pwd, int count);

int main(int argc, string argv[])
{
    // max length password, encrypted password and salt
    int const PWDLEN = 8, CRYPTLEN = 15, SALTLEN = 2;
    // maximum number of tries necessary using brute force assuming 8 character password: 95^8
    long const MAXTRIES = (long) pow(95, 8);
    
    // check for invalid input; did not check for invalid characters in input
    if (argc != 2)
    {
        printf("INVALID INPUT\n");
        return 1;
    }

    // declare char arrays for password to be encrypted (pwd), encrypted password (pwdEncr) and salt
    char pwd[PWDLEN], pwdEncr[CRYPTLEN], salt[SALTLEN];
    // ptrMsg = a pointer to encrypted input; ptrPwd = a pointer to encrypted try-value
    char *ptrMsg = argv[1], *ptrPwd = pwdEncr;
    char *ptrSalt = salt;

     // get salt; first 2 chars of input
    for (int i = 0; i < 2; i++)
    {
        ptrSalt[i] = argv[1][i];
    }
    
    // print salt as a check
    printf("salt is: %s\n", ptrSalt);
    
    for (int i = 1; i < MAXTRIES; i++)
    {
        // do base conversion
        baseConv(pwd, i);
        // now encrypt the converted password
        ptrPwd = crypt(pwd, ptrSalt);
        
        // if password matches exit loop
        if (strcmp(ptrPwd, ptrMsg) == 0)
        {
            printf("password: %s", pwd);
            return 0;
        }
    }
    return 0;
}

/*
 function converts numbers to base 95 using printable ASCII chars (#32 - 126)
 note that converted numbers are stored in reverse order
*/
void baseConv(char * pwd, int count)
{
    // initialize base to be counted in (= number of printable chars)
    // specify where to start counting in ASCII table (= number first printable char)
    int const BASE = 95, START_ASCII = 32; 
    int remain = 0, number = count, j = 0;
    
    // convert the number to base 95 using printable ASCII chars
    while (number > 0)
    {
        number--;
        // calculate remainder of number
        remain = number % BASE;
        // convert remainder number to respective printable character
        pwd[j] = remain + START_ASCII;
        // divide number by base
        number = number / BASE;
        j++;
    }
    // end string here
    pwd[j+1] = '\0';
}
