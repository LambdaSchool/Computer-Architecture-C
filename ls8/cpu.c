#include "cpu.h"

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  char data[DATA_LEN] = {
      // From print8.ls8
      0b10000010, // LDI R0,8
      0b00000000,
      0b00001000,
      0b01000111, // PRN R0
      0b00000000,
      0b00000001 // HLT
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
    // TODO
    break;
    // TODO: implement more ALU ops
    // case ALU_ADD:
    //   break;

    // case ALU_SUB:
    //   break;

    // case ALU_DIV:
    //   break;

    // case ALU_MOD:
    //   break;

    // case ALU_INC:
    //   break;

    // case ALU_DEC:
    //   break;

    // case ALU_CMP:
    //   break;

    // case ALU_AND:
    //   break;

    // case ALU_NOT:
    //   break;

    // case ALU_OR:
    //   break;

    // case ALU_XOR:
    //   break;

    // case ALU_SHL:
    //   break;

    // case ALU_SHR:
    //   break;
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
    // TODO
    // 1. Get the value of the current instruction (in address PC).
    unsigned char ir = cpu_ram_read(cpu, cpu->PC);
    unsigned char operandA = cpu_ram_read(cpu, cpu->PC + 1);
    unsigned char operandB = cpu_ram_read(cpu, cpu->PC + 2);
    // 2. switch() over it to decide on a course of action.
    switch (ir)
    {
    case LDI:

      break;
    case PRN:
      // printf()
      break;
    case HLT:
      running = 0;
      break;
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
  //key value stored at address 0xF4 if stack is empty
  cpu->registers[8] = 0xF4;
  // TODO: Zero registers and RAM
  //memset(starting address of memory to be filled, value to be filled, Number of bytes to be filled starting at address[0])
  memset(cpu->registers, 0, sizeof cpu->registers);
  memset(cpu->ram, 0, sizeof cpu->ram);
}

unsigned char cpu_ram_read(struct cpu *cpu, unsigned char mar)
{
  //read from memory address
  return cpu->ram[mar];
}

unsigned char cpu_ram_write(struct cpu *cpu, unsigned char mar, unsigned char mdr)
{
  //write value to memory
  cpu->ram[mar] = mdr;
}
