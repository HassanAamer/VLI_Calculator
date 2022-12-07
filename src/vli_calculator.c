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

    printf("VLI1: ");
    if (VLI1->isNegative)
    {
        printf("-");
    }
    printf("%s\n", VLI1->VLI_value);
    printf("VLI2: ");
    if (VLI2->isNegative)
    {
        printf("-");
    }
    printf("%s\n", VLI2->VLI_value);

    vli_t *sum = addSignedVLIs(VLI1, VLI2);
    printf("Sum: ");
    if (sum->isNegative)
    {
        printf("-");
    }
    printf("%s\n", sum->VLI_value);

    free(VLI1->VLI_value);
    free(VLI1);
    free(VLI2->VLI_value);
    free(VLI2);
    free(sum->VLI_value);
    free(sum);
    return 0;
}