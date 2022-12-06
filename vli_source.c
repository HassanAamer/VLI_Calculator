#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHUNK 200

char *readVLIasChar(char *Path);

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

    printf("VLI1: %s\nVLI2: %s", VLI1, VLI2);

    free(VLI1);
    free(VLI2);
    return 0;
}

char *readVLIasChar(char *Path)
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