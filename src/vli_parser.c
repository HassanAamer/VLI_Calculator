#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vli_parser.h"

#define CHUNK 200
#define ASCII_OFFSET 48

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

    VLIlength--;
    new_VLI->isNegative = read_isNegative;
    new_VLI->VLI_value = VLI_read_value;
    new_VLI->length = VLIlength - read_isNegative;
    return new_VLI;
}

vli_t *normalizeVLI(vli_t *VLI)
{
    size_t length = VLI->length;
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
        VLI->length = 1;
        return VLI;
    }

    VLI->length = length - i;
    reversedValue = strrev(VLI->VLI_value);
    reversedValue[VLI->length] = '\0';
    VLI->VLI_value = strrev(reversedValue);

    return VLI;
}

// These functions assist in the two-sided conversion between ASCII & Integers

int convertASCIIToInt(char c)
{
    return c - ASCII_OFFSET;
}

char convertIntToASCII(int i)
{
    return i + ASCII_OFFSET;
}