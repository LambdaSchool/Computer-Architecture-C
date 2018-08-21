#include <stdio.h>
#include "cpu.h"

/**
 * ALU
 */
// void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
// {
//   switch (op) {
//     case ALU_MUL:
//       // TODO
//       break;

//     // TODO: implement more ALU ops
//   }
// }

/**
 * CPU Instruction: Halts the CPU and exits emulator
 * 
 * @param running {int*} Pointer to cpu loop variable.
 */
void handle_HLT(int *running)
{
  *running = 0;
}

/**
 * CPU Instruction: Sets value of register to an integer
 * 
 * @param registers {unsigned char[]} Register array.
 * @param reg {unsigned char} Register number.
 * @param immediate {unsigned char} value to be stored in register.
 */
void handle_LDI(unsigned char registers[], unsigned char reg, unsigned char immediate)
{
  registers[reg] = immediate;
}

/**
 * CPU Instruction: Prints numeric value stored in given register
 * 
 * @param registers {unsigned char[]} Register array.
 * @param reg {unsigned char} Register number.
 */
void handle_PRN(unsigned char registers[], unsigned char reg)
{
  printf("%d\n", registers[reg]);
}

/**
 * Reads from RAM address and stores value into store
 * 
 * @param ram {unsigned char[]} Memory array.
 * @param address {unsigned char} Address for memory array.
 * @param store {unsigned char*} Pointer to location value at memory address should be stored.
 */
void cpu_ram_read(unsigned char ram[], unsigned char address, unsigned char *store)
{
  *store = ram[address];
}

/**
 * Writes data to RAM address 
 * 
 * @param ram {unsigned char[]} Memory array.
 * @param address {unsigned char} Address for memory array.
 * @param data {unsigned char} data to be stored at memory address.
 */
void cpu_ram_write(unsigned char ram[], unsigned char address, unsigned char data)
{
  ram[address] = data;
}

/**
 * Converts a decimal to a binary representation
 * 
 * @param d {unsigned char} integer value to convert.
 * @param b {int*} Pointer to array where binary representation is stored.
 */
void decimal_to_binary(unsigned char d, int *b)
{
  int n = d;
  int i = 7;

  while (n > 0)
  {
    b[i] = n % 2;
    n /= 2;
    --i;
  }
}

/**
 * Determines whether binary instruction has one argument
 * 
 * @param binary {int*} Pointer to array where binary representation is stored.
 * 
 * @returns boolean.
 */
int hasOpA(int *binary)
{
  return (binary[0] == 0 && binary[1] == 1) || (binary[0] == 1 && binary[1] == 0);
}

/**
 * Determines whether binary instruction has second argument
 * 
 * @param binary {int*} Pointer to array where binary representation is stored.
 * 
 * @returns boolean.
 */
int hasOpB(int *binary)
{
  return binary[0] == 1 && binary[1] == 0;
}

/**
 * Initialize a CPU struct
 * 
 * Initializes the PC and other special registers. -> TODO
 * Zeros registers and RAM. -> TODO
 * 
 * @param cpu {struct cpu*} Pointer to a cpu struct.
 */
void cpu_init(struct cpu *cpu)
{
  cpu->pc = 0b00000000;
}

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu)
{
  const int DATA_LEN = 6;
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
 * Run the CPU
 * 
 * @param cpu {struct cpu*} Pointer to a cpu struct.
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1;

  while (running) {
    unsigned char operandA = '\0';
    unsigned char operandB = '\0';
    int irb[8] = {0};
    cpu_ram_read(cpu->ram, cpu->pc, &cpu->ir);
    decimal_to_binary(cpu->ir, irb);

    if (hasOpA(irb))
    {
      cpu->pc++;
      cpu_ram_read(cpu->ram, cpu->pc, &operandA);
    }

    if (hasOpB(irb))
    {
      cpu->pc++;
      cpu_ram_read(cpu->ram, cpu->pc, &operandB);
    }

    switch (cpu->ir)
    {
      case HLT:
        handle_HLT(&running);
        break;
      case LDI:
        handle_LDI(cpu->registers, operandA, operandB);
        break;
      case PRN:
        handle_PRN(cpu->registers, operandA);
        break;
    }

    cpu->pc++;
  }
}