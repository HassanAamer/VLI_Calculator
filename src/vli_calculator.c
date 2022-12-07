#include <stdio.h>
#include <stdlib.h>
#include "vli_addition.h"
#include "vli_reader.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Not enough command line arguments!");
    }

    char *VLI1_path = argv[1];
    char *VLI2_path = argv[2];

    char *VLI1 = readVLI(VLI1_path);
    char *VLI2 = readVLI(VLI2_path);

    printf("VLI1: %s\nVLI2: %s\n", VLI1, VLI2);

    char *sum = addVLIs(VLI1, VLI2);
    printf("Sum: %s\n", sum);

    free(VLI1);
    free(VLI2);
    free(sum);
    return 0;
}