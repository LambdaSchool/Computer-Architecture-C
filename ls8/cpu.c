#include "cpu.h"
#include <stdio.h>
#include <stdlib.h>

unsigned char cpu_ram_read(struct cpu *cpu, unsigned char address) 
{
  return cpu->ram[address];
}
 void cpu_ram_write(struct cpu *cpu, unsigned char address, unsigned char value) 
{
  cpu->ram[address] = value;
}

 void cpu_load(struct cpu *cpu, char *file)
{	 
  FILE * f;
  f = fopen(file, "r");	      
  if (f == NULL )
  {
    fprintf(stderr, "Cannot open file.\n");
    exit(1);
  }

  int address = 0;
  
  char line[256];

  while (fgets(line, sizeof(line), f)) {
    char *endptr;
    unsigned long int new_line;
    new_line = strtoul(line, &endptr, 2);
    cpu->ram[address++] = new_line;
  }
  fclose(f);
  // TODO: Replace this with something less hard-coded
}

void pop(struct cpu *cpu, unsigned char reg) {
  cpu->reg[reg] = cpu->reg[7];
  cpu->reg[7] ++;
}
void push(struct cpu *cpu, unsigned char reg) 
 {
	  cpu->reg[7] --;
	  cpu->reg[7] = cpu->reg[reg];
 }
/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      cpu->reg[regA] = cpu->reg[regA] * cpu->reg[regB];
      break;

    // TODO: implement more ALU ops
    case ALU_ADD:
      cpu->reg[regA] = cpu->reg[regA] + cpu->reg[regB];
    	break;	      
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    // 2. switch() over it to decide on a course of action.
    // 3. Do whatever the instruction should do according to the spec.
    // 4. Move the PC to the next instruction.

    unsigned char IR = cpu_ram_read(cpu, cpu->pc);
    unsigned char operandA = cpu_ram_read(cpu, cpu->pc+1);
    unsigned char operandB = cpu_ram_read(cpu, cpu->pc+2);

    switch(IR) {    
    
      case LDI:
        cpu->reg[operandA] = operandB;
        cpu->pc += 3;
        break;
    
     case PRN:
        printf("print8: %d", cpu->reg[operandA]);
        cpu->pc += 2;
        break;
   
      case HLT:
        running = 0;
        break;
      
      case ADD:
        alu(cpu, ALU_ADD, operandA, operandB);
        break;
    
      case MUL:
        alu(cpu, ALU_MUL, operandA, operandB);
        break;
      
      case PUSH:
        push(cpu, operandA);
        break;
      
      case POP: 
       pop(cpu, operandA);
       break;
    
    default:
        printf("unknown instruction: %02x, %02x", cpu->pc, IR);
        exit(2);
    }
     cpu->pc += (IR >> 6) + 1;
  }	  
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->pc = 0;

  cpu->reg[SP] = 0xf4;
  // TODO: Zero registers and RAM
}
