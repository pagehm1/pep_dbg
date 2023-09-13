/*
    Project Name: pep_dbg
    Purpose: A vritual machine designed to execute and debug pep9 programs. It will also be able to give statistics and insights on the code.
*/
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>
#include "cpu.h"

//global values
struct CPU cpu;
struct hsearch_data *CommandArgs; //general commands of the programs
struct hsearch_data *Debug_CommandArgs; //debugging commands


void initialize_HashTables()
{
    //all general commands of the program
    char *commandArgNames[] = { "alpha", "bravo", "charlie", "delta",
        "echo", "foxtrot", "golf", "hotel", "india", "juliet",
        "kilo", "lima", "mike", "november", "oscar", "papa",
        "quebec", "romeo", "sierra", "tango", "uniform",
        "victor", "whisky", "x-ray", "yankee", "zulu"
    };

    //all commands for the debugging portion
    char *debug_CommandArgNames[] = {
        "alpha", "bravo", "charlie", "delta",
        "echo", "foxtrot", "golf", "hotel", "india", "juliet",
        "kilo", "lima", "mike", "november", "oscar", "papa",
        "quebec", "romeo", "sierra", "tango", "uniform",
        "victor", "whisky", "x-ray", "yankee", "zulu"
    };

    //initialize hash tables
    CommandArgs = calloc(1, sizeof(struct hsearch_data));
    Debug_CommandArgs = calloc(1, sizeof(struct hsearch_data));

    /*
        https://linux.die.net/man/3/hcreate_r
        Hash table implementations are usually more efficient when the table contains enough free space to minimize collisions. 
        Typically, this means that nel should be at least 25% larger than the maximum number of elements that the caller expects to 
        store in the table.
    */
    int result;
    result = hcreate_r(30, CommandArgs);

    if(result == 0)
    {
        fprintf(stderr, "entry failed on CommandArgs\n");
        exit(EXIT_FAILURE);
    }

    result = hcreate_r(30, Debug_CommandArgs);
    if(result == 0)
    {
        fprintf(stderr, "entry failed on Debug_CommandArgs\n");
        exit(EXIT_FAILURE);
    }

    //Hash table entries
    ENTRY e, *ep;
    int i;

    for(i = 0; i < 10; i++)
    {
        e.key = commandArgNames[i];
        e.data = (void *)(long) i;

        if (hsearch_r(e, ENTER, &ep, CommandArgs) == 0) {
            fprintf(stderr, "entry failed\n");
            exit(EXIT_FAILURE);
        }
    }

    for(i=0; i < 10; i++)
    {
        e.key = commandArgNames[i];
        e.data = (void *)(long) i;

        if (hsearch_r(e, ENTER, &ep, Debug_CommandArgs) == 0) {
            fprintf(stderr, "entry failed\n");
            exit(EXIT_FAILURE);
        }
    }

    //TESTING HASH TABLES
    /*
        for(i = 0; i < 10; i++)
    {
        e.key = commandArgNames[i];
        if (hsearch_r(e, FIND, &ep, CommandArgs) == 0) {
            ep = NULL;
        }


        printf("%9.9s -> %9.9s:%p\n", e.key,
               ep ? ep->key : "NULL", ep ? (void *)(long)(ep->data) : 0);

        e.key = commandArgNames[i+11];

        if (hsearch_r(e, FIND, &ep, Debug_CommandArgs) == 0) {
            ep = NULL;
        }


        printf("%9.9s -> %9.9s:%p\n", e.key,
               ep ? ep->key : "NULL", ep ? (void *)(long)(ep->data) : 0);

    }
    */
}


/*
    performs all necessary actions to start the program
*/
void initialize_Program()
{
    initialize_CPU(&cpu);
    initialize_HashTables();
}



int main(int argc, char *argv[])
{
    //run until we receive an end signal from the user or an error occurs
    while(1)
    {
        //init program
        initialize_Program();
        
        printf("%d %d %d %d %d %d", cpu.Accumulator, cpu.Index, cpu.InstructionRegister, cpu.ProgramCounter, cpu.StackPointer, cpu.StatusRegisters);

        
        //wait for the user to enter a command
        char *input;
        size_t bufsize = 1000;
        input = (char *)malloc(bufsize * sizeof(char));
        if( input == NULL)
        {
            perror("Unable to allocate space for input");
            exit(1);
        }

        printf("(pep)$: ");
        getline(&input, &bufsize, stdin);
    }

    

    return 0;
}
