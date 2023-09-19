/*
    Project Name: pep_dbg
    Purpose: A vritual machine designed to execute and debug pep9 programs. It will also be able to give statistics and insights on the code.
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>
#include <stdint.h>
#include <ctype.h>
#include <unistd.h>
#include "cpu.h"

//global values
struct CPU cpu;
struct hsearch_data *CommandArgs; //general commands of the programs
struct hsearch_data *Debug_CommandArgs; //debugging commands

//all general commands of the program
char *commandArgNames[] = { 
    "help", "load", "exec", 
    "memdump", "regdump", "dump", 
    "srcdump", "stats", "clean",
    "exit"
};

//all commands for the debugging portion
char *debug_CommandArgNames[] = {
    "verbose", "tail", "memdump",
    "regdump", "dump", "srcdump",
    "continue", "remove", "add",
    "exit"
};

void initialize_HashTables()
{
    //initialize hash tables
    CommandArgs = calloc(1, sizeof(struct hsearch_data));
    Debug_CommandArgs = calloc(1, sizeof(struct hsearch_data));

    //get size of array of command names
    int commandSize = sizeof(commandArgNames) / sizeof(commandArgNames[0]);

    /*
        https://linux.die.net/man/3/hcreate_r
        Hash table implementations are usually more efficient when the table contains enough free space to minimize collisions. 
        Typically, this means that nel should be at least 25% larger than the maximum number of elements that the caller expects to 
        store in the table.
    */
    int tableSize = commandSize + (commandSize*0.5);
    
    int result;
    result = hcreate_r(tableSize, CommandArgs);

    if(result == 0)
    {
        fprintf(stderr, "entry failed on CommandArgs\n");
        exit(EXIT_FAILURE);
    }

    result = hcreate_r(tableSize, Debug_CommandArgs);
    if(result == 0)
    {
        fprintf(stderr, "entry failed on Debug_CommandArgs\n");
        exit(EXIT_FAILURE);
    }

    //Hash table entries
    ENTRY e, *ep;
    int i;

    //enter all commands and their integer values
    for(i = 0; i < commandSize; i++)
    {
        e.key = commandArgNames[i];
        e.data = (void *)(intptr_t) i+1;

        if (hsearch_r(e, ENTER, &ep, CommandArgs) == 0) {
            fprintf(stderr, "entry failed\n");
            exit(EXIT_FAILURE);
        }

        e.key = debug_CommandArgNames[i];
        e.data = (void *)(intptr_t) i+1;

        if (hsearch_r(e, ENTER, &ep, Debug_CommandArgs) == 0) {
            fprintf(stderr, "entry failed\n");
            exit(EXIT_FAILURE);
        }
    }

    /*
    //TESTING HASH TABLES
    for(i = 0; i < commandSize; i++)
    {
        e.key = commandArgNames[i];
        if (hsearch_r(e, FIND, &ep, CommandArgs) == 0) {
            ep = NULL;
        }

        printf("%9.9s -> %9.9s:%p\n", e.key,
               ep ? ep->key : "NULL", ep ? (void *)(intptr_t)(ep->data) : 0);

        e.key = debug_CommandArgNames[i];
        if (hsearch_r(e, FIND, &ep, Debug_CommandArgs) == 0) {
            ep = NULL;
        }

        printf("%9.9s -> %9.9s:%p\n", e.key,
               ep ? ep->key : "NULL", ep ? (void *)(intptr_t)(ep->data) : 0);
        

    }
    */

    //printf("done");
}


/*
    performs all necessary actions to start the program
*/
void initialize_Program()
{
    initialize_CPU(&cpu);
    initialize_HashTables();
}

void exit_Program()
{
    //free values
    free(CommandArgs);
    free(Debug_CommandArgs);
    exit(EXIT_SUCCESS);
}

void load(struct CPU* cpu)
{

}

int main(int argc, char *argv[])
{
    //run until we receive an end signal from the user or an error occurs
    while(1)
    {
        //init program
        initialize_Program();
        
        size_t bufsize = 1000;
        //wait for the user to enter a command
        char *input;
        input = (char *)malloc(bufsize * sizeof(char));
        if(input == NULL)
        {
            fprintf(stderr, "Unable to allocate space for input");
            exit(EXIT_FAILURE);
        }

        printf("(pep)$: ");
        getline(&input, &bufsize, stdin);
        
        //start parsing what was typed in
        //char *subtoken;
        char *token;
        char **args = malloc(1 * sizeof(char *)); 
        int i = 0;
        
        //separate the user input by strings into a dynamically allocated string array
        while(token = strsep(&input, " "))
        {
            int length = strlen(token);
            
            args[i] = (char *)malloc(strlen(token) + 1);
            args[i] = token;
            args[i][strcspn(args[i], "\n")] = 0; //let's remove the newline at the end since it is messing up the check for the hash table
            i++;
            args = realloc(args, i+1 * sizeof(char *)); //add another space for arg list
        }
        
        

        //lowercase the command
        for(int i = 0; i < strlen(args[0]); i++){
            args[0][i] = tolower(args[0][i]);
        }


        ENTRY e, *ep;
        e.key = args[0];
        int success = hsearch_r(e, FIND, &ep, CommandArgs);

        int command_data = ep ? (intptr_t)ep->data: 0;

        //handles argument parsing and passing those values to the method that performs the necessary logic
        switch(command_data)
        {
            case 1:
                break;
            case 2: //load
                load(&cpu);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9: //clean program

                initialize_CPU(&cpu);
                break;
            case 10: //exit program
                exit_Program();
                break;
            default:
                printf("command not found, use \"help\" to see a list of commands\n");
                break;
        }

        //free temp values
        free(input);
        free(token);
        for(int i = 0; i < sizeof(args) / sizeof(char *); i++)
        {
            free(args[i]);
        }
        free(args);
    }

    return 0;
}
