#ifndef _CPU_H_
#define _CPU_H_

// Holds all information about the CPU
struct cpu {
  // TODO
  // PC
  // registers (array)
  // ram (array)
  unsigned int PC;
  unsigned char registers[8]; // we're emulating an 8 bit cpu
  unsigned char ram[256]; // 2^8 is 256
  
};

// ALU operations
enum alu_op {
	ALU_MUL,
  ALU_ADD,
  ALU_SUB,
  ALU_DIV,
  ALU_INC,
  ALU_DEC,
	// Add more here
};

// Instructions

// These use binary literals. If these aren't available with your compiler, hex
// literals should be used.

#define LDI  0b10000010
#define HLT  0b00000001
#define PRN  0b01000111
// TODO: more instructions here. These can be used in cpu_run().

// Function declarations

extern void cpu_load(struct cpu *cpu);
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif
