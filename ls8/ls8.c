#include <stdio.h>
#include "cpu.h"

/**
 * Main
 */
int main(int argc, char **argv[])
// int main(void)
{
    struct cpu cpu; // more flexible

    if (argc != 2)
    {
        fprintf(stderr, "usage: ls8 filename\n");
        exit(1);
    }

    char *filename = argv[1];

    cpu_init(&cpu);
    cpu_load(&cpu, filename);
    // cpu_load(&cpu);
    cpu_run(&cpu);

    return 0;
}

// int main(void)
// {
//     struct cpu *cpu = cpu_create();

//     cpu_load(&cpu);
//     cpu_run(&cpu);

//     cpu_destroy(cpu);

//     return 0;
// }