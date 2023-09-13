#ifndef _CPU
#define _CPU

#include <stdio.h>

/*
    contains all of the values of the cpu
*/
struct CPU
{
    unsigned int StatusRegisters : 4; //1 bit for each flag: Negative(N), Zero(Z), Overflow(V), Carry(c)
    unsigned int Accumulator : 16;
    unsigned int Index : 16;
    unsigned int ProgramCounter : 16;
    unsigned int StackPointer : 16;
    unsigned int InstructionRegister : 24;
    unsigned char Memory[65536]; 
};

void initialize_CPU(struct CPU* cpu);

#endif