#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vli_parser.h"

#define CHUNK 200

char convertIntToASCII(int i);
int convertASCIIToInt(char c);

vli_t *readVLI(char *Path)
{
    FILE *f = fopen(Path, "r");
    char *VLI_read_value = NULL;
    char signcheck;
    int read_isNegative;
    long VLI_start_offset = 0L;
    int VLIlength = 0;

    vli_t *new_VLI = malloc(sizeof(vli_t));
    if ((signcheck = fgetc(f)) == '-')
    {
        read_isNegative = 1;
        VLI_start_offset = 1L;
    }
    else
    {
        fseek(f, 0L, SEEK_SET);
        read_isNegative = 0;
    }

    fseek(f, 0L, SEEK_END);
    VLIlength = ftell(f) + 1;
    fseek(f, VLI_start_offset, SEEK_SET);

    VLI_read_value = (char *)malloc(sizeof(char) * VLIlength);
    VLI_read_value = fgets(VLI_read_value, VLIlength, f);

    fclose(f);

    new_VLI->isNegative = read_isNegative;
    new_VLI->VLI_value = VLI_read_value;
    return new_VLI;
}

vli_t *normalizeVLI(vli_t *VLI)
{
    size_t length = strlen(VLI->VLI_value);
    char *reversedValue;

    int i = 0;
    while ((convertASCIIToInt(VLI->VLI_value[i]) == 0))
    {
        i++;
    }

    if (i == length)
    {
        VLI->isNegative = POSITIVE;
        VLI->VLI_value[0] = '0';
        VLI->VLI_value[1] = '\0';
        return VLI;
    }

    reversedValue = strrev(VLI->VLI_value);
    reversedValue[length - i] = '\0';
    VLI->VLI_value = strrev(reversedValue);

    return VLI;
}

// These functions assist in the two-sided conversion between ASCII & Integers

int convertASCIIToInt(char c)
{
    return c - 48;
}

char convertIntToASCII(int i)
{
    return i + 48;
}