#ifndef _CPU_H_
#define _CPU_H_

// Holds all information about the CPU
struct cpu {
  // TODO
  // PC   `PC`: Program Counter, address of the currently executing instruction
  unsigned char pc;
  // registers (array)  -- only 8 slots
  unsigned char registers[8];
  // ram (array)  -- he said in lecture that it would only be 256 bytes i thinl
  unsigned char ram[256]; //creates array with 256 open slots
  unsigned char SP; // Creates the stack pointer / references most recently pushed or address F4
  unsigned int E; // For the CMP command
};

// ALU operations
enum alu_op {
	ALU_MUL,
  ALU_CMP
	// Add more here
};

// Instructions

// These use binary literals. If these aren't available with your compiler, hex
// literals should be used

#define LDI  0b10000010
#define HLT  0b00000001
#define PRN  0b01000111
#define MUL 0b10100010
#define PUSH 0B01000101
#define POP  0B01000110
// Subroutine Calls
#define CALL 0b01010000
#define RET 0b00010001
#define CMP 0b10100111
#define JNE 0b01010110 
#define JMP 0b01010100
#define JEQ 0b01010101
// TODO: more instructions here. These can be used in cpu_run().

// Function declarations

extern void cpu_load(struct cpu *cpu, char *argv[]);
extern void cpu_init(struct cpu *cpu);
extern void cpu_run(struct cpu *cpu);

#endif
