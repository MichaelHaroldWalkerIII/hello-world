// -----------------------------------------------------------------------
// File: proj1.c
//
// Name: Michael Walker
//
// Description: This program changes lower-case characters into
//      upper-case characters and vice versa, as well as 
//      counting up to a number entered between 0 and 25.
//
// Syntax:
//      Input is entered into the command line terminal, and that is also
//      where output appears.
// -----------------------------------------------------------------------
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

int main(int argc, char *argv[])
{
        //Define variables
        int i;
        int len=strlen(argv[1]);
        long num;
        char a[len];

        //Check inputs
        if (argc != 3) {   
                printf("Invalid number of inputs \n");
                exit (-1);
        }

        //Convert character case in strings
        for(i=0;i<=len;i++) {
                if (isupper(argv[1][i])) {
                        a[i]=tolower(argv[1][i]);
        } else {
                        a[i]=toupper(argv[1][i]);
                }
        }
        printf("%s\n", a);

        //Display numbers
        num=strtol(argv[2], NULL, 10);
        if ((num>0)&&(num<25)) {
                for(i=1;i<=num;i++) {
                printf("%i, ", i);
                }
                printf("\n");         
        } else { 
                printf("Invalid number \n");
                exit(-1);
                }
        return 0;
}
