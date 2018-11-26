#ifndef _CPU_H_
#define _CPU_H_

// Holds all information about the CPU
// funcs in ls8.c are also declared here

struct cpu {
  // PC (program counter)
  unsigned char PC;
  // registers (array)
  unsigned char reg[8];
  // ram (array)
  unsigned char ram[256];
  // Flage
  unsigned char FL;
};

// ALU operations
enum alu_op {
  ALU_ADD,
  ALU_SUB,
	ALU_MUL,
  ALU_DIV,
	// Add more here
};

// Instructions

// These use binary literals. If these aren't available with your compiler, hex
// literals should be used.

#define LDI  0b10000010
#define PRN  0b01000111
#define HLT  0b00000001
#define MUL  0b10100010
#define POP  0b01000110
#define PUSH  0b01000101
#define ADD  0b10100000
#define DIV  0b10100011
#define SUB  0b10100001
#define CMP  0b10100111
#define JMP  0b01010100
#define JEQ  0b01010101
#define JNE  0b01010110

#define FLAG  0x00

// TODO: more instructions here. These can be used in cpu_run().

// Function declarations

extern void cpu_load(struct cpu *cpu, char *filename);
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif
