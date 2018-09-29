//--------------------------------------------------------------------------
// File: shell.c
//
// Name: Michael Walker
//
// Description: This program creates a command-line shell with different
// responses to various prompts.
//
// Syntax: Input is entered into the command-line terminal, and that is 
// also where output appears.

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<ctype.h>
#include<string.h>
#include<signal.h>
#include<unistd.h>
#include<signal.h>
#include<time.h>
#include<sys/wait.h>


#define ARG_NUMBER 11
#define BUFSIZE 100
#define EXIT 30
#define SUCCESS 0
#define YES 1

//Signal functions
void alarm_handler(int signal)
{
        fprintf(stdout, "\nThe session has expired.\nExiting...\n");
        exit(-3);
}

void segmentation_handler(int signal)
{
        fprintf(stderr, "\nA segmentation fault has been detected. \nExiting...\n");
        exit(-2);
}

void controlC_handler(int signal)
{
        fprintf(stdout, "\nGood try... I don't die that easily.\n");
        fprintf(stdout, "Enter 'exit' at the prompt to terminate this shell.\n");
}

int main(int argc, char *argv[])
{
        //Local variables
        char line[BUFSIZE];
        int i;
        pid_t pid;

        //Alarm signal setup
        struct sigaction act;
        act.sa_handler = &alarm_handler;
        sigemptyset(&act.sa_mask);
        act.sa_flags = SA_RESTART;
        sigaction(SIGALRM, &act, NULL);
        if(sigaction(SIGALRM, &act, NULL) == -1) {
                fprintf(stderr, "SIGALRM signal error\n");
        }
        alarm(EXIT);
        
        //Segmentation fault signal setup
        struct sigaction segmentation_fault;
        segmentation_fault.sa_handler = segmentation_handler;
        sigemptyset(&segmentation_fault.sa_mask);
        segmentation_fault.sa_flags = SA_RESTART;
        sigaction(SIGSEGV, &segmentation_fault, NULL);
        if (sigaction(SIGSEGV, &segmentation_fault, NULL) == -1) {
                fprintf(stderr, "SIGSEGV signal error\n");
        }

        //Control-C signal setup
        struct sigaction control;
        control.sa_handler = controlC_handler;
        sigemptyset(&control.sa_mask);
        control.sa_flags = SA_RESTART;
        sigaction(SIGINT, &control, NULL);
        if(sigaction(SIGINT, &control, NULL) == -1) {
                fprintf(stderr, "SIGINT signal error\n");
        }

        while(YES) {

                //Define arguments as a character array
                char *arguments[ARG_NUMBER];
                for(i=0;i<ARG_NUMBER;++i) {
                        arguments[i] = NULL;
                }
                printf("prompt>");

                //Accept user input and replace \n with \0
                fgets(line, BUFSIZE, stdin);
                size_t length = strlen(line);
                if(line[length-1] == '\n');
                line[length-1] = '\0';

                char *token = NULL;
                token = strtok(line, " ");
                if(token == NULL) {
                        continue;
                }

                //"exit" terminates program
                if(strcmp(token, "exit") == 0) {
                        break;
                }

                //"explode" causes segmentation fault
                if(strcmp(token, "explode") == 0) {
                        int *bomb=NULL;
                        *bomb=42;
                }

                //Split commands
                int i = 0;
                while(token != NULL) {
                        arguments[i++] = token;
                        token=strtok(NULL, " ");
                }

                //Start shell
                pid = fork();
                if(pid < 0) {
                        fprintf(stderr, "Child process error\n");
                        exit(-1);
                } else if(pid == 0) {
                        execvp(arguments[0], arguments);
                        fprintf(stderr, "Exec failure\n");
                } else {
                        waitpid(pid, NULL, WUNTRACED);
                }
                return(SUCCESS);
        }
}
