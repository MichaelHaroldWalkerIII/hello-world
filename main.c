//--------------------------------------------------------------------------
//
//Name: Michael Walker
//
//Description: This program will fill up a dynamically allocated array 
//with potentially large random numbers. It will then use different 
//approaches to add up the numbers in the array.
//
//Syntax: Input is entered into the command line terminal, and that
//is also where output appears. 
//
//--------------------------------------------------------------------------
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<time.h>
#include<stdarg.h>
#include<limits.h>
#include<unistd.h>
#include<sys/ioctl.h>

#define SUCCESS 0
#define CHAR_RED "\033[31m"
#define CHAR_RESET "\033[0m"
#define ELEMENTS 100
#define MAXIMUM 1234567890

void display(unsigned int values[], unsigned int num_values);

int main(void)
{
        //Declare variables
        errno = 0;
        int num_values = 0;
        int i;

        //Seed the random number generator
        srandom(time(NULL));
        
        //Generate random numbers
        num_values = (random() % ELEMENTS + 1);
        
        //Allocate memory for array
        
        unsigned int *values = NULL;
        
        values = malloc(num_values*sizeof(unsigned int));

        //Error Checking
        if ((errno != 0) || (values == NULL)) {
                printf("Error");
                exit(-1);
        }

        //Create array
        for (i = 0;i<num_values;i++) {
                values[i] = (random() % MAXIMUM);
        }
        
        //Display array
        display(values, num_values);
        free(values);
        values = NULL;
        return SUCCESS;
}

void display(unsigned int values[], unsigned int num_values)
{       
        unsigned int k;
        unsigned int subtotal_with_rollover = 0;
        unsigned int subtotal_without_rollover = 0;
        unsigned long long subtotal_rollover = 0;

        //Create and display header
        printf("%13s %13s %13s %13s\n", "", "unsigned", "unsigned", "unsigned");
        printf("%13s %13s %13s %13s\n", "", "int", "int", "long long");
        printf("%13s %13s %13s %13s\n", "", "Subtotal", "Subtotal", "Subtotal");
        printf("%13s %13s %13s %13s\n", "Random", "w/ Rollover", "w/o Rollover", "w/o Rollover");
        printf("%13s %13s %13s %13s\n", "Number", "Detection", "Detection", "Subtotal");
        printf("%13s %13s %13s %13s\n", "-------------", "-------------", "-------------", "-------------");
        
        //Fill columns of display
        for (k = 0;k<=num_values;k++) {
                subtotal_with_rollover = values[k] + subtotal_with_rollover;
                subtotal_without_rollover = values[k] + subtotal_without_rollover;
                if ((subtotal_with_rollover > 0) && (subtotal_with_rollover > (UINT_MAX - values[k]))) {
                        subtotal_rollover = values[k] + subtotal_rollover;
                        printf("%13u", values[k]);
                        printf(CHAR_RED);
                        printf("%14s", "REJECTED");
                        printf(CHAR_RESET);
                        printf("%14u %13llu\n", subtotal_without_rollover, subtotal_rollover);
                } else {
                        subtotal_rollover = values[k] + subtotal_rollover;
                        printf("%13u %13u %13u %13llu\n", values[k], subtotal_with_rollover, subtotal_without_rollover, subtotal_rollover);
                } 
        }
}
