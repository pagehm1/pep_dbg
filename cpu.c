#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    initializes the pep9 processor memory, registers and flags.
    memory will stay empty until the program is passed in
*/
void initialize_CPU(struct CPU* cpu)
{
    cpu->Accumulator = 0;
    cpu->Index = 0;
    cpu->InstructionRegister = 0;
    cpu->ProgramCounter = 0;
    cpu->StackPointer = 0;

    memset(cpu->Memory, 0, 65536);
}

/*
void load_CPU(struct CPU* cpu)
{

}
*/
