#include "cpu.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DATA_LEN 6

/**
 * Load the binary bytes from a .ls8 source file into a RAM array
 */
void cpu_load(char *filename, struct cpu *cpu)
{
//char data[DATA_LEN] = {
// From print8.ls8
//  0b10000010, // LDI R0,8
//  0b00000000,
//  0b00001000,
//  0b01000111, // PRN R0
//   0b00000000,
//  0b00000001  // HLT
//  };

 // int address = 0;

 // for (int i = 0; i < DATA_LEN; i++) {
 //   cpu->ram[address++] = data[i];
 // }

 // TODO: Replace this with something less hard-coded
FILE *p;
char line[256];
int count = 0; 
if ((p=fopen(filename,"r"))==NULL){
fprintf(stderr, "file not open %s \n",filename);
exit(1);
}
#if DEBUG
     printf("\n**********Lines from file:***********\n");
     #endif
while (fgets(line, sizeof(line), p) != NULL) { 
      char *ptr;
      unsigned char byte = strtoul(line, &ptr, 2);
      if (ptr == line) {
        continue;
      }
      cpu->ram[count++] = byte;
      #if DEBUG
      printf("Value of line: %s", line);
      #endif
    }

    #if DEBUG
    printf("\nRAM in Load\n");
    for (unsigned long i = 0; i < 256; i++) {
      printf("cpu->ram[%lu] = %u\n", i, cpu->ram[i]);
    }
    #endif

}
unsigned char cpu_ram_read(struct cpu *cpu, int index){
  return cpu->ram[index];
}
void cpu_ram_write(struct cpu *cpu, unsigned char address, unsigned char value)
{
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
    unsigned char operandA = NULL;
    unsigned char operandB = NULL;
    // TODO
    // 1. Get the value of the current instruction (in address PC).
   unsigned char instruction = cpu_ram_read(cpu,cpu->PC);

    
    // 2. Figure out how many operands this next instruction requires
    unsigned int num_operands = instruction >> 6;


    // 3. Get the appropriate value(s) of the operands following this instruction
     if(num_operands==2){
       operandA = cpu_ram_read(cpu,(cpu->PC+1)& 0xff);
     }else if( num_operands==1){
       operandA = cpu_ram_read(cpu,(cpu->PC+1)& 0xff);
     }else{}
    // 4. switch() over it to decide on a course of action.
    switch (instruction)
    {
      case HLT:
      running = 0;
      break;
      case PRN:
      printf("d\n",cpu -> reg[operandA]);
      break;
      case LDI:
       cpu->reg[operandA]= operandB;
    // 5. Do whatever the instruction should do according to the spec.
    // 6. Move the PC to the next instruction.
  }
}

/**
 * Initialize a CPU struct
 */
void cpu_init(struct cpu *cpu)
{
  // TODO: Initialize the PC and other special registers
cpu->PC = 0;
  memset(cpu->reg, 0, sizeof cpu->reg);
  memset(cpu->ram, 0, sizeof cpu->ram);



}
