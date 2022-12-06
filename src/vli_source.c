#include <stdio.h>
#include <stdlib.h>
#include "vliaddition.h"

#define CHUNK 200
#define ASCII_OFFSET 48

char *readVLIasChar(char *Path);
char *addVLIs(char *VLI1, char *VLI2);
char convertIntToASCII(int i);
int convertASCIIToInt(char c);

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Not enough command line arguments!");
    }

    char *VLI1_path = argv[1];
    char *VLI2_path = argv[2];

    char *VLI1 = readVLIasChar(VLI1_path);
    char *VLI2 = readVLIasChar(VLI2_path);

    printf("VLI1: %s\nVLI2: %s\n", VLI1, VLI2);

    char *sum = addVLIs(VLI1, VLI2);
    printf("Sum: %s\n", sum);

    free(VLI1);
    free(VLI2);
    free(sum);
    return 0;
}