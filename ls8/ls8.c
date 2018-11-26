#include <stdio.h>
#include "cpu.h"

/**
 * Main  -- intializes the cpu
 */
int main(int argc, char **argv)
{
  struct cpu cpu;

  if (argc != 2) {
    fprintf(stderr, "Usage: ls8 filename.ls8\n");
    return 1;
  }

  cpu_init(&cpu);
  cpu_load(&cpu, argv[1]);
  cpu_run(&cpu);

  return 0;
}