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
    0b00000001  // HLT
  };

  int address = 0;

  for (int i = 0; i < DATA_LEN; i++) {
    cpu->ram[address++] = data[i];
  }

  // TODO: Replace this with something less hard-coded / step 8
}

unsigned char cpu_ram_read(struct cpu *cpu, unsigned char address)
{
  return cpu->ram[address];
}

void cpu_ram_write(struct cpu *cpu, unsigned char address, unsigned char value)
{
  return cpu->ram[address] = value;
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
 * DAY - 1 / Step 4 
 * Run the CPU
 */
/*
Meanings of the bits in the first byte of each instruction: `AABCDDDD`

* `AA` Number of operands for this opcode, 0-2
* `B` 1 if this is an ALU operation
* `C` 1 if this instruction sets the PC
* `DDDD` Instruction identifier

The number of operands `AA` is useful to know because the total number of bytes in any
instruction is the number of operands + 1 (for the opcode). This
allows you to know how far to advance the `PC` with each instruction.

operandA = cpu_read_ram(cpu->pc + 1)

*/
void cpu_run(struct cpu *cpu)
{
  int running = 1; // True until we get a HLT instruction 
  unsigned char IR; //store that result in `IR` ... This can just be a local
  unsigned char operandA;//into variables `operandA` and `operandB` in case the instruction needs them
  unsigned char operandB;
 

  while (running) {
    // TODO
    // 1. Get the value of the current instruction (in address PC)./ IR
    IR = cpu_ram_read(cpu, cpu->PC);
    // 2. Figure out how many operands this next instruction requires
    // 3. Get the appropriate value(s) of the operands following this instruction
    operandA = cpu_ram_read(cpu, cpu->PC+1);
    operandB = cpu_ram_read(cpu, cpu->PC+2);
    // 4. switch() over it to decide on a course of action.
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.
  }
}

/**
 * DAY - 1 / Step 3 
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers 
  // At first, the PC, registers, and RAM should be cleared to zero.
  cpu->PC = 0;
  memset(cpu->reg, 0, sizeof(cpu->reg));
  memset(cpu->ram, 0, sizeof(cpu->ram));
  //(`memset()` might help you clear registers and RAM.)
    // man pages -  void *memset(void *s, int c, size_t n);
    // function fills the first n bytes of the memory area pointed to by s with the constant byte c.
}

