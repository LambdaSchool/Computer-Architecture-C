#include <stdlib.h>
#include <stdio.h>
#include "cpu.h"

/**
 * Main
 */
int main(int argc, char *argv[])
{
  struct cpu cpu;

  if (argc != 2) {
    fprintf(stderr, "Unrecognized input. Usage: ./ls8 <filename>\n");
    exit(1);
  }

  cpu_init(&cpu);
  cpu_load(&cpu, argv);
  cpu_run(&cpu);

  return 0;
}