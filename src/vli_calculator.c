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

    vli_t *VLI1 = readVLI(VLI1_path);
    if (VLI1 == NULL)
    {
        printf("VLI1 cannot be empty!");
        return 1;
    }
    vli_t *VLI2 = readVLI(VLI2_path);
    if (VLI2 == NULL)
    {
        printf("VLI2 cannot be empty!");
        return 1;
    }

    printf("VLI1 SIGN: %d, VLI2 SIGN: %d\n", VLI1->isNegative, VLI2->isNegative);
    printf("VLI1: %s\nVLI2: %s\n", VLI1->VLI_value, VLI2->VLI_value);

    vli_t *sum = addVLIs(VLI1, VLI2);
    printf("Sum: %s\n", sum->VLI_value);

    free(VLI1->VLI_value);
    free(VLI1);
    free(VLI2->VLI_value);
    free(VLI2);
    free(sum->VLI_value);
    free(sum);
    return 0;
}