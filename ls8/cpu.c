#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, char *file)
{
  FILE * fp = fopen(file, "r");  
  if (fp == NULL) {
    fprintf(stderr, "There was an error opening the file\n");
    exit(1);
  }

  int index = 0;
  char buffer[256];
  char *pointer;

  while(fgets(buffer, sizeof(buffer), fp) != NULL) {
    cpu->ram[index++] = strtoul(buffer, &pointer, 2);
  }

};


unsigned char cpu_ram_read(struct cpu *cpu, unsigned char address) {
  return cpu->ram[address];
}

void cpu_ram_write(struct cpu *cpu, unsigned char address, unsigned char value) {
  cpu->ram[address] = value;
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op) {
    case ALU_MUL:
      // TODO
      break;

    case ALU_ADD:
      break;

    // TODO: implement more ALU ops
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
    unsigned char IR = cpu_ram_read(cpu, cpu->PC);
    unsigned char operandA = cpu_ram_read(cpu, cpu->PC+1);
    unsigned char operandB = cpu_ram_read(cpu, cpu->PC+2);

    // 2. switch() over it to decide on a course of action.
    switch(IR) {
      case LDI:
        cpu->reg[operandA] = operandB;
        cpu->PC += 3;
        break;

      case PRN:
        printf("%d\n", cpu->reg[operandA]);
        cpu->PC += 2;
        break;
      
      case MUL:
        cpu->reg[operandA] = cpu->reg[operandA] * cpu->reg[operandB];
        cpu->PC += 3;
        break;

      case HLT:
        running = 0;
        break;
      
      default:
        printf("Unknown instruction at %02x: %02x\n", cpu->PC, IR);
        exit(2);
    }

    // 3. Do whatever the instruction should do according to the spec.

    // 4. Move the PC to the next instruction.

  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->PC = 0;
  // TODO: Zero registers and RAM
}
