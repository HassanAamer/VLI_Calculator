#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vli_reader.h"

#define CHUNK 200

vli_t *readVLI(char *Path)
{
    FILE *f = fopen(Path, "r");
    char *VLI_read_value = NULL;
    char tempbuffer[CHUNK];
    char *returncheck = NULL;
    char signcheck;
    int read_isNegative = -1;
    size_t templength = 0, VLIlength = 0;

    vli_t *new_VLI = malloc(sizeof(vli_t));
    if ((signcheck = fgetc(f)) == '-')
    {
        read_isNegative = 1;
    }
    else
    {
        if (signcheck != EOF)
        {
            VLIlength = 1;
            char *tmp = realloc(VLI_read_value, (VLIlength + 1) * sizeof(char));
            if (tmp == NULL)
            {
                printf("ERROR\n");
            }
            VLI_read_value = tmp;
        }
        VLI_read_value[0] = signcheck;
        VLI_read_value[1] = '\0';
        read_isNegative = 0;
    }

    while ((returncheck = fgets(tempbuffer, CHUNK, f)) != NULL)
    {
        // Resize VLI to accomodate next part of VLI
        templength = strlen(tempbuffer);
        char *tmp = realloc(VLI_read_value, (templength + VLIlength) * sizeof(char));
        if (tmp == NULL)
        {
            printf("ERROR\n");
        }
        VLI_read_value = tmp;

        // Append the new part of the VLI to the existing VLI
        strcpy(VLI_read_value + VLIlength, tempbuffer);
        VLIlength += templength;
    }

    fclose(f);

    if (read_isNegative == -1)
    {
        return NULL;
    }

    new_VLI->isNegative = read_isNegative;
    new_VLI->VLI_value = VLI_read_value;
    return new_VLI;
}