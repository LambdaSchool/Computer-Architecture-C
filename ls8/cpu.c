#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>

unsigned char cpu_ram_read(struct cpu *cpu, unsigned char MAR)
{
  return cpu->ram[MAR];
}

void cpu_ram_write(struct cpu *cpu, unsigned char MAR, unsigned char MDR)
{
  cpu->ram[MAR] = MDR;
}
/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  const int DATA_LEN = 6;
  char data[6] = {
      // From print8.ls8
      // 0b10000010, // LDI R0,8
      // 0b00000000,
      // 0b00001000,
      // 0b01000111, // PRN R0
      // 0b00000000,
      // 0b00000001 // HLT

      10000010, //# LDI R0,8
      00000000,
      00001000,
      10000010, //# LDI R1,9
      00000001,
      00001001,
      10100010, // # MUL R0,R1
      00000000,
      00000001,
      01000111, // # PRN R0
      00000000,
      00000001, // # HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++)
  {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  switch (op)
  {
  case ALU_MUL:
    cpu->reg[regA] = cpu->reg[regA] * cpu->reg[regB];
    break;

  case ALU_ADD:
    cpu->reg[regA] = cpu->reg[regA] + cpu->reg[regB];
    break;

  case ALU_DIV:
    cpu->reg[regA] = cpu->reg[regA] / cpu->reg[regB];
    break;

  case ALU_SUB:
    cpu->reg[regA] = cpu->reg[regA] - cpu->reg[regB];
    break;

  case ALU_INC:
    cpu->reg[regA] += 1;
    break;

  case ALU_DEC:
    cpu->reg[regA] -= 1;
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

  while (running)
  {
    unsigned char IR = cpu_ram_read(cpu, cpu->pc);

    unsigned char operandA = cpu_ram_read(cpu, cpu->pc + 1);

    unsigned char operandB = cpu_ram_read(cpu, cpu->pc + 2);

    printf("TRACE: %02x: %02x\n", cpu->pc, IR);
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    // unsigned const char IR = ram->
    // 2. switch() over it to decide on a course of action.
    switch (IR)
    {
    case LDI:
      cpu->reg[operandA] = operandB;
      // cpu->pc += 3;
      break;

      // void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
    case MUL:
      alu(cpu, ALU_MUL, operandA, operandB);
      // cpu->pc += 3;
      break;

    case PRN:
      printf("%d\n", cpu->reg[operandA]);
      // cpu->pc += 2;
      break;

    case HLT:
      running = 0;
      break;

    default:
      printf("Unknown instruction at %02x: %02x\n", cpu->pc, IR);
      exit(2);
      // break;
    }
    // 3. Do whatever the instruction should do according to the spec.

    // 4. Move the PC to the next instruction.
    //PC + 1 or PC + 2
    const int move = (IR >> 6) + 1;
    cpu->pc += move;
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
  cpu->pc = 0;
  // TODO: Zero registers and RAM
}
