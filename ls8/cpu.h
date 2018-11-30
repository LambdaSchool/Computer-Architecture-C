#ifndef _CPU_H_
#define _CPU_H_

// Holds all information about the CPU
struct cpu {
  // TODO
  int PC; // PC
  unsigned char registers[8]; // registers (array)
  unsigned char ram[256]; // ram (array)
};

// ALU operations
enum alu_op {
	ALU_MUL
	// Add more here
};
#define SP 5
#define EMPTY_STACK  0xf4
// Instructions

// These use binary literals. If these aren't available with your compiler, hex
// literals should be used.
// TODO: more instructions here. These can be used in cpu_run().
#define HLT  0b00000001
#define LDI  0b10000010
#define PRN  0b01000111
#define MUL  0b10100010
#define PUSH  0b01000101
#define POP  0b01000110

// Function declarations

extern void cpu_load(char *filename, struct cpu *cpu);
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif
