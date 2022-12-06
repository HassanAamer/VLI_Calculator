#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ASCII_OFFSET 48
#define CHUNK 200

char *readVLIasChar(char *Path);
char *addVLIs(char *VLI1, char *VLI2);
char convertIntToASCII(int i);
int convertASCIIToInt(char c);

char *addVLIs(char *VLI1, char *VLI2)
{
    char *sum = NULL;
    size_t VLI1_length = strlen(VLI1);
    size_t VLI2_length = strlen(VLI2);
    int carry_flag = 0;
    int temp_sum;

    char *smaller_length_VLI;
    char *bigger_length_VLI;

    if (VLI1_length > VLI2_length)
    {
        bigger_length_VLI = strrev(VLI1);
        smaller_length_VLI = strrev(VLI2);
    }
    else
    {
        smaller_length_VLI = strrev(VLI2);
        bigger_length_VLI = strrev(VLI1);
    }

    size_t smaller_length = strlen(smaller_length_VLI);
    size_t bigger_length = strlen(bigger_length_VLI);

    size_t length_diff = bigger_length - smaller_length;

    sum = (char *)malloc(sizeof(char) * (strlen(bigger_length_VLI) + 2));

    int i;
    int second_term;

    for (i = 0; i < bigger_length; i++)
    {
        second_term = (i >= smaller_length) ? 0 : convertASCIIToInt(smaller_length_VLI[i]);
        temp_sum = convertASCIIToInt(bigger_length_VLI[i]) + second_term + carry_flag;

        if (temp_sum >= 10)
        {
            temp_sum -= 10;
            carry_flag = 1;
        }
        else
        {
            carry_flag = 0;
        }

        sum[i] = convertIntToASCII(temp_sum);
    }

    if (carry_flag)
    {
        sum[i] = '1';
        i++;
    }
    sum[i] = '\0';

    return strrev(sum);
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

int convertASCIIToInt(char c)
{
    return c - 48;
}

char convertIntToASCII(int i)
{
    return i + 48;
}