#ifndef _CPU_H_
#define _CPU_H_

// Holds all information about the CPU
struct cpu {
  // TODO
  // PC
  unsigned char PC;

  // registers (array)
  unsigned char reg[8];

  // ram (array)
  unsigned char ram[256];
};

// ALU operations
enum alu_op {
	// Add more here
  ALU_ADD,
  ALU_AND,
	ALU_MUL,
};

// Instructions

// These use binary literals. If these aren't available with your compiler, hex
// literals should be used.
// TODO: more instructions here. These can be used in cpu_run().

#define ADD  0b10100000
#define AND  0b10101000
#define CALL 0b01010000
#define LDI  0b10000010
#define HLT  0b00000001
#define PRN  0b01000111

// Function declarations

extern void cpu_load(struct cpu *cpu);
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif
