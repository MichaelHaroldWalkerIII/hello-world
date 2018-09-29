// -----------------------------------------------------------------------
// File: dots.c
//
// Name: Michael Walker
//
// Description: This program displays a requested number of '*' (dots)
// at random locations of the terminal.
//
// Syntax: Input is entered into the command line terminal, and that is
// also where output appears.
// -----------------------------------------------------------------------
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<sys/ioctl.h>
#include<time.h>
#include<unistd.h>

#define ARG_STRING 2
#define CLEAR_SCREEN "\033[2J"
#define MOVE_CURSOR "\033[%d;%dH"

void display_dots(int num_dots)
{
        int i;
        int max_rows = 0;
        int max_cols = 0;
        int x = 0;
        int y = 0;
        struct winsize win;
        
        ioctl(0, TIOCGWINSZ, &win);
        max_rows = win.ws_row;
        max_cols =  win.ws_col;
        printf(CLEAR_SCREEN);        
        
        for (i=1;i<=num_dots;++i) {
                x = (random() % max_cols) + 1;
                y = (random() % max_rows) + 1;
                printf(MOVE_CURSOR, y, x);
                sleep(1);
                printf("*");
                fflush(stdout);
        }
        printf(MOVE_CURSOR, max_rows, 1);
}

int main(int argc, char *argv[]) 
{       
        //Define variables
        long num_dots;
        char *ch=NULL;
        errno=0;

        //Verify valid number of arguments
        if (argc != ARG_STRING) {   
                printf("Invalid number of inputs \n");             
                exit (-1);
        }

        //Convert argv[1] to a number
        num_dots=strtol(argv[1], &ch, 10);
        if((errno!=0)||(*ch!='\0')) {
                printf("invalid number \n");
                exit(-1);
        }

        //Verify number is in valid range
        if (!(num_dots>=1)&&!(num_dots<=1000)) { 
                printf("Invalid number \n");
                exit(-1);
        }
        
        //Seed the random number generator
        srandom(time(NULL));

        //Call display_dots function
        
        display_dots(num_dots);

        return 0;
}
