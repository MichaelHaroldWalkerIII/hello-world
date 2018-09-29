//----------------------------------------------------
// File: mycopy.c
//
// Name: Michael Walker
//
// Description: This program copies from a source
// file to a destination file while changing lower-case characters
// to upper-case.
//
//
// Syntax: Input is entered into the command line terminal, and that is
// also where output appears.
// -----------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<ctype.h>
#include<string.h>

#define ARG_STRING 3
#define BUFSIZE 128
#define SUCCESS 0

int main(int argc, char *argv[]) 
{
        char *source = argv[1];
        char *destination = argv[2];
        FILE *file1=NULL;
        FILE *file2=NULL;
        char buf[BUFSIZE];
        size_t Source_read;
        size_t Destination_write;
        int count = 0;
        int lines = 0;
        int punctuated = 0;
        
        //Check number of arguments
        if(argc != ARG_STRING) {
                printf("Error: Not the correct number of files \n");
                exit(-1);
        }

        //Verify if source and destination files are the same
        if (strcmp(source, destination)==0) {
                printf("Error: Source and destination files are identical \n");
                exit(-1);
        }

        //Error handling
        if (errno!=0) {
                perror("Error \n");
                exit(-1);
                fflush(stderr);
                fflush(stdout);
        }

        //Copy from source to destination file and change case of characters
        errno = SUCCESS;
        file1 = fopen(source, "r");
        if (errno != SUCCESS) {
                fprintf(stderr, "Unable to open '%s': %s\n", source, strerror(errno));
                exit(-1);
        } if (source == NULL) {
                printf("Error: File does not exist \n");
                exit(-1);
        } if (( file2 = fopen(destination, "r"))) {
                printf("Error: File already exists \n");
                exit(-1);
        }
 
        //Verify if destination file can be created
        if (!fopen(destination, "w")) {
                printf("Error: Destination file could not be created \n");
                exit(-1);
        }
        Source_read = fread(buf, 1,strlen(buf), file1);

        for(int i=0; i<=strlen(buf); i++) {
                if(islower(buf[i])){
                        buf[i] = toupper(buf[i]);
                        count++;
                } 
                if(ispunct(buf[i])!=0) {
                        punctuated++;
                } 
                if(buf[i]=='\n') {
                        lines++;
                }
        } 

        file2 = fopen(destination, "w");

        do {
        Destination_write = fwrite(buf, 1, Source_read, file2);
        if(Destination_write>0) {
                buf[Destination_write] = '\0';
                } else if (ferror(file2));
                break;
        } while (!feof(file2));
        printf("%s %i\n", "Number of characters copied:", strlen(buf));
        printf("%s %i\n", "Number of characters changed:", count);
        printf("%s %i\n", "Number of lines in the file:", lines); 
        printf("%s %i\n", "Number of punctuation chars:", punctuated);
        
        // clean up
        if (file1 != NULL) {
                fclose(file1);
                file1 = NULL;
        }
        if (file2 != NULL) {
                fclose(file2);
                file2 = NULL;
        }
        return SUCCESS;
}

