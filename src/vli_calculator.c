#include <stdio.h>
#include <stdlib.h>
#include "vli_addition.h"
#include "vli_parser.h"

void printVLI(vli_t *VLI);
void freeVLI(vli_t *VLI);

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

    VLI1 = normalizeVLI(VLI1);
    VLI2 = normalizeVLI(VLI2);

    /* printf("VLI1: ");
    printVLI(VLI1);
    printf("VLI2: ");
    printVLI(VLI2); */

    vli_t *sum = addSignedVLIs(VLI1, VLI2);

    printf("Sum: ");
    printVLI(sum);

    freeVLI(VLI1);
    freeVLI(VLI2);
    freeVLI(sum);
    return 0;
}

void printVLI(vli_t *VLI)
{
    if (VLI->isNegative)
    {
        printf("-");
    }
    printf("%s\n", VLI->VLI_value);
}

void freeVLI(vli_t *VLI)
{
    free(VLI->VLI_value);
    free(VLI);
}