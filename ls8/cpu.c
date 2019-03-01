#include "cpu.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(struct cpu *cpu, char *filename)
{
  FILE *fp = fopen(filename, "r");
  char line[8192];
  int address = 0;
  while (fgets(line, sizeof(line), fp) != NULL)
  {
    char *endpointer;
    unsigned char val = strtoul(line, &endpointer, 2);
    if (endpointer == line)
    {
      continue;
    }
    cpu_ram_write(cpu, address++, val);
  }
  fclose(fp);
}

/**
 * ALU
 */
void alu(struct cpu *cpu, enum alu_op op, unsigned char regA, unsigned char regB)
{
  unsigned char valA = cpu->registers[regA];
  unsigned char valB = cpu->registers[regB];
  switch (op)
  {
  case ALU_MUL:
    cpu->registers[regA] = valA * valB;
    break;

    // TODO: implement more ALU ops
  }
}

/**
 * Run the CPU
 */
void cpu_run(struct cpu *cpu)
{
  int running = 1;

  while (running)
  {
    unsigned char _IR = cpu_ram_read(cpu, cpu->pc);
    unsigned char flag = 0;

    // TODO: refactor with bitwise operations
    int _operands;
    if (_IR > 0b00111111 && _IR < 0b10000000)
    {
      _operands = 1;
    }
    if (_IR >= 0b10000000)
    {
      _operands = 2;
    }

    unsigned char operandA = cpu_ram_read(cpu, cpu->pc + 1);
    unsigned char operandB = cpu_ram_read(cpu, cpu->pc + 2);

    switch (_IR)
    {

    case ADD: // ADD registerA registerB // --> ALU
      /*Add the value in two registers and store the result 
      in registerA.*/
      break;

    case AND: // AND registerA registerB // --> ALU
      /*Bitwise-AND the values in registerA and registerB, 
      then store the result in registerA.*/
      break;

    case CALL: // CALL register //
      /*Calls a subroutine (function) at the address stored 
      in the register.*/
      /*The address of the instruction directly after CALL is 
      pushed onto the stack. This allows us to return to where 
      we left off when the subroutine finishes executing.*/
      cpu->registers[7]--;
      cpu->ram[cpu->registers[7]] = cpu->pc + 1;

      /*The PC is set to the address stored in the given register. 
      We jump to that location in RAM and execute the first 
      instruction in the subroutine. The PC can move forward 
      or backwards from its current location.*/
      cpu->pc = cpu->registers[operandA];
      flag = 1;
      break;

    case CMP: // CMP registerA registerB //
      /*Compare the values in two registers:
      equal, set the Equal E flag to 1, otherwise set it to 0.
      A is less than registerB, set the Less-than L flag to 1, 
      otherwise set it to 0.
      A is greater than registerB, set the Greater-than G 
      flag to otherwise set it to 0.*/
      break;

    case DEC: // DEC register // --> ALU
      /*Decrement (subtract 1 from) the value in the given register.*/
      break;

    case DIV: // DIV registerA registerB // --> ALU
      /*Divide the value in the first register by the value 
      in the second, storing the result in registerA.
      If the value in the second register is 0, the system 
      should print an error message and halt.*/
      break;

    case HLT: // HLT //
      /*Halt the CPU (and exit the emulator).*/
      printf("--done exiting--\n");
      exit(0);
      break;

    case INC: // INC register //
      /*Increment (add 1 to) the value in the given register.*/
      break;

    case INT: // INT register //
      /* Issue the interrupt number stored in the given register.
      This will set the _n_th bit in the IS register to the value 
      in the given register. */
      flag = 1;
      break;

    case IRET: // IRET //
      /*The following steps are executed:
      Registers R6-R0 are popped off the stack in that order.
      The FL register is popped off the stack.
      The return address is popped off the stack and stored in PC.
      Interrupts are re-enabled*/
      flag = 1;
      break;

    case JEQ: // JEQ register //
      /*If equal flag is set (true), jump to the address 
      stored in the given register.*/
      flag = 1;
      break;

    case JGE: // JGE register //
      /*If greater-than flag or equal flag is set (true), 
      jump to the address stored in the given register.*/
      flag = 1;
      break;

    case JGT: // JGT register //
      /*If greater-than flag is set (true), jump to the 
      address stored in the given register.*/
      flag = 1;
      break;

    case JLE: // JLE register //
      /*If less-than flag or equal flag is set (true), 
      jump to the address stored in the given register.*/
      flag = 1;
      break;

    case JLT: // JLT register //
      /*If less-than flag is set (true), jump to the address 
      stored in the given register.*/
      flag = 1;
      break;

    case JMP: // JMP register //
      /*Jump to the address stored in the given register.
      Set the PC to the address stored in the given register.*/
      flag = 1;
      break;

    case JNE: // JNE register //
      /*If E flag is clear (false, 0), jump to the address 
      stored in the given register.*/
      flag = 1;
      break;

    case LD: // LD registerA registerB //
      /*Loads registerA with the value 
      at the memory address stored in registerB.
      This opcode reads from memory.*/
      break;

    case LDI: // LDI register immediate //
      /*Set the value of a register to an integer.*/
      // printf("setting register %u to %u\n", operandA, operandB); // <-- debugging
      cpu->registers[operandA] = operandB;
      break;

    case MOD: // MOD registerA registerB //
      /*Divide the value in the first register by 
      the value in the second, storing the remainder 
      of the result in registerA.
      If the value in the second register is 0, 
      the system should print an error message and halt.*/
      break;

    case MUL: // MUL registerA registerB // --> ALU
      /*Multiply the values in two registers together 
      and store the result in registerA.*/
      alu(cpu, ALU_MUL, operandA, operandB);
      break;

    case NOP: // NOP //
      /*No operation. Do nothing for this instruction.*/
      break;

    case NOT: // NOT register //
      /*Perform a bitwise-NOT on the value in a register.*/
      break;

    case OR: // OR registerA registerB //
      /*Perform a bitwise-OR between the values in registerA 
      and registerB, storing the result in registerA.*/
      break;

    case POP: // POP register //
      /*Pop the value at the top of the stack into the given register.
      Copy the value from the address pointed to by SP to the given 
      register.
      Increment SP.*/
      cpu->registers[operandA] = cpu->ram[cpu->registers[7]];
      cpu->registers[7]++;
      break;

    case PRA: // PRA register //
      /*Print alpha character value stored in the given register.
      Print to the console the ASCII character corresponding to the 
      value in the register.*/
      break;

    case PRN: // PRN register //
      /*Print numeric value stored in the given register.
      Print to the console the decimal integer value that 
      is stored in the given register.*/
      printf("%u\n", cpu->registers[operandA]);
      break;

    case PUSH: // PUSH register //
      /*Push the value in the given register on the stack.
      Decrement the SP.
      Copy the value in the given register to the address 
      pointed to by SP.*/
      cpu->registers[7]--;
      cpu->ram[cpu->registers[7]] = cpu->registers[operandA];
      break;

    case RET: // RET //
      /*Return from subroutine.
      Pop the value from the top of the stack and store it in the PC.*/
      cpu->pc = cpu->ram[cpu->registers[7]];
      cpu->registers[7]++;
      flag = 1;
      break;

    case SHL: // SHL //
      /*This is an instruction handled by the ALU.
      Shift the value in registerA left by the number of bits 
      specified in registerB, filling the low bits with 0.*/
      break;

    case SHR: // SHR // --> ALU
      /*Shift the value in registerA right by the number of bits 
      specified in registerB, filling the high bits with 0.*/
      break;

    case ST: // ST registerA registerB //
      /*Store value in registerB in the address stored in registerA.
      This opcode writes to memory.*/
      break;

    case SUB: // SUB registerA registerB // --> ALU
      /*Subtract the value in the second register from the 
      first, storing the result in registerA.*/
      break;

    case XOR: // XOR registerA registerB //
      /*Perform a bitwise-XOR between the values in registerA 
      and registerB, storing the result in registerA.*/
      break;

    default:
      printf("unknown command %u\n", _IR);
      running = 0;
      exit(1);
      break;
    }
    if (flag == 0)
    {
      cpu->pc = cpu->pc + _operands + 1;
    }
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  cpu->pc = 0;
  memset(cpu->ram, 0, sizeof(cpu->ram));
  memset(cpu->registers, 0, sizeof(cpu->registers));
  cpu->registers[7] = 243;
}

unsigned char cpu_ram_read(struct cpu *cpu, int index)
{
  return cpu->ram[index];
}

void cpu_ram_write(struct cpu *cpu, int index, unsigned char value)
{
  cpu->ram[index] = value;
  return;
}
