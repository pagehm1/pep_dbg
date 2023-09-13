#include "cpu.h"
#include <stdio.h>

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

    
}