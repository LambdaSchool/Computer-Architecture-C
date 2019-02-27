#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cpu.h"
#define DATA_LEN 6

unsigned char cpu_ram_read(struct cpu *cpu, unsigned char mar)
{
  // mar = Memory Address Register, holds the memory address
  // we're reading or writing

  // return value from ram specified by mar
  return cpu->ram[mar];
}

void cpu_ram_write(struct cpu *cpu, unsigned char mar, unsigned char mdr)
{
  // mdr = Memory Data Register, holds the value
  // to write or the value just read

  // write mdr in ram
  cpu->ram[mar] = mdr;
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, char *filename)
{
  FILE *fp = fopen(filename, "r");

  if (fp == NULL)
  {
    fprintf(stderr, "ls8: error opening file:  %s\n", filename);
    exit(2);
  }

  char line[8192]; // to hold individual lines in the file
  int address = 0;

  while (fgets(line, sizeof(line), fp) != NULL)
  {
    char *endptr; // to keep track of non-numbers in the file
    // converts str to number
    unsigned char byte = strtoul(line, &endptr, 2);

    // prevents unnecessary lines being stored on ram
    if (endptr == line)
    {
      continue;
    }

    cpu->ram[address++] = byte;
  }

  fclose(fp);
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op)
  {
  case ALU_MUL:
    // TODO
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
  unsigned char IR, operand0, operand1;

  while (running)
  {
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    IR = cpu_ram_read(cpu, cpu->PC);

    // 2. Figure out how many operands this next instruction requires
    // 3. Get the appropriate value(s) of the operands following this instruction
    operand0 = cpu_ram_read(cpu, cpu->PC + 1);
    operand1 = cpu_ram_read(cpu, cpu->PC + 2);

    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.
    switch (IR)
    {
    case LDI:
      // sets value of operand1 to the reg[operand0]
      cpu->reg[operand0] = operand1;
      // Move the PC to the next instruction.
      cpu->PC += 3;
      break;
    case PRN:
      printf("%d\n", cpu->reg[operand0]);
      // Move the PC to the next instruction.
      cpu->PC += 2;
      break;
    case HLT:
      // Set running to false to stop program
      running = 0;
      // Move the PC to the next instruction.
      cpu->PC += 1;
      break;
    default:
      printf("Unexpected instruction 0x%02X at 0x%02X\n", IR, cpu->PC);
      exit(1);
    }
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers

  // R0-R6 are cleared to 0
  for (int i = 0; i < 6; i++)
  {
    cpu->reg[i] = 0;
  }

  // R7 is set to 0xF4
  cpu->reg[7] = 0xF4;

  // PC is cleared to 0
  cpu->PC = 0;

  // RAM is cleared to 0
  memset(cpu->ram, 0, sizeof(cpu->ram));
}
