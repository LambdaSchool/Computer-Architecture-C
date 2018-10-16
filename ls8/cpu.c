#include "cpu.h"

#define DATA_LEN 6

/**
 * HELPER FUNCTIONS
 *  cpu_ram_read()
 *  cpu_ram_write()
 */
unsigned char cpu_ram_read(struct cpu *cpu, unsigned char address) 
{
  return cpu->ram[address];
}

void cpu_ram_write(struct cpu *cpu, unsigned char address, unsigned char value)
{
  cpu->ram[address] = value;
}


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
    0b00000001  // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++) {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded
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
       // `IR`: Instruction Register, contains a copy of the currently executing instruction
    unsigned char IR = cpu_ram_read(cpu, cpu->pc);
    unsigned char operandA = cpu_ram_read(cpu, cpu->pc+1);
    unsigned char operandB = cpu_ram_read(cpu, cpu->pc+2);


     // True if this instruction might set the PC
    int instruction_set_pc = (IR >> 4) & 1;


    // 2. switch() over it to decide on a course of action.
    // 3. Do whatever the instruction should do according to the spec.

    switch(IR)
    {
       // `LDI`: load "immediate", store a value in a register, or "set this register to.
      case LDI:
        void

       // `PRN`: a pseudo-instruction that prints the numeric value stored in a register.
      case PRN:
        void

       // `HLT`: halt the CPU and exit the emulator.
      case HLT:
        void


      default:
        fprintf(strderr, "ERROR: Unknown Instruction\n from cpu_run() in cpu.c\n PC: %02x\n IR: %02X\n", cpu->PC, IR);
        exit(3);
    } // <-- END OF switch -->


    // 4. Move the PC to the next instruction.

       // `>>` (right shift) Takes two numbers, right shifts the bits of the first operand, the second operand decides the number of places to shift.
       // `&` (bitwise AND) Takes two numbers as operands and does AND on every bit of two numbers. The result of AND is 1 only if both bits are 1.
       // https://www.geeksforgeeks.org/bitwise-operators-in-c-cpp/

    if (!instruction_set_pc)
    {
      cpu->PC += ((IR >> 6) & 0x3) +1;
    }

  } // <-- END OF while loop -->
} // <-- END OF cpu_run() -->

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers

  // TODO: Zero registers and RAM
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */

