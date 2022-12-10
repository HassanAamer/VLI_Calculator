#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vli_parser.h"

#define CHUNK 200

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
    return NULL;
}