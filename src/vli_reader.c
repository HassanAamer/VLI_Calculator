#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHUNK 200

char *readVLI(char *Path)
{
    FILE *f = fopen(Path, "r");
    char *VLI = NULL;
    char tempbuffer[CHUNK];
    char *returncheck = NULL;
    size_t templength = 0, VLIlength = 0;
    while ((returncheck = fgets(tempbuffer, CHUNK, f)) != NULL)
    {
        // Resize VLI to accomodate next part of VLI
        templength = strlen(tempbuffer);
        char *tmp = realloc(VLI, (templength + VLIlength) * sizeof(char));
        if (tmp == NULL)
        {
            printf("ERROR\n");
        }
        VLI = tmp;

        // Append the new part of the VLI to the existing VLI
        strcpy(VLI + VLIlength, tempbuffer);
        VLIlength += templength;
    }

    fclose(f);

    return VLI;
}