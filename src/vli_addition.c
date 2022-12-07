#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vli_reader.h"

#define ASCII_OFFSET 48
#define NO_CARRY 0
#define BASE_10 10
#define CARRY 1
#define NEGATIVE 1
#define POSITIVE 0

vli_t *addSignedVLIs(vli_t *VLI1, vli_t *VLI2);
vli_t *addUnsignedVLIs(vli_t *VLI1, vli_t *VLI2);
char convertIntToASCII(int i);
int convertASCIIToInt(char c);

vli_t *addSignedVLIs(vli_t *VLI1, vli_t *VLI2)
{
    vli_t *sum = NULL;
    if (VLI1->isNegative && VLI2->isNegative)
    {
        sum = addUnsignedVLIs(VLI1, VLI2);
        sum->isNegative = NEGATIVE;
    }
    else if (!VLI1->isNegative && !VLI2->isNegative)
    {
        sum = addUnsignedVLIs(VLI1, VLI2);
        sum->isNegative = POSITIVE;
    }
    else
    {
        if (isGreaterThan(VLI1, VLI2))
        {
            sum = subtractVLIs(VLI1, VLI2);
            sum->isNegative = (VLI1->isNegative) ? NEGATIVE : POSITIVE;
        }
        else
        {
            sum = subtractVLIs(VLI2, VLI1);
            sum->isNegative = (VLI2->isNegative) ? NEGATIVE : POSITIVE;
        }
    }
    return sum;
}

vli_t *subtractVLIs(vli_t *minuend, vli_t *subtractend)
{
}

int isGreaterThan(vli_t *VLI1, vli_t *VLI2)
{
    size_t VLI1_length = strlen(VLI1->VLI_value);
    size_t VLI2_length = strlen(VLI2->VLI_value);

    if (VLI1_length > VLI2_length)
    {
        return true;
    }
    else if (VLI2_length > VLI1_length)
    {
        return false;
    }
    else
    {
        int i = 0;
        while (VLI1->VLI_value[i] == VLI2->VLI_value[i])
        {
            i++;
        }
        return (VLI1->VLI_value[i] > VLI2->VLI_value[i]);
    }
}

vli_t *addUnsignedVLIs(vli_t *VLI1, vli_t *VLI2)
{
    vli_t *sum = NULL;
    size_t VLI1_length = strlen(VLI1->VLI_value);
    size_t VLI2_length = strlen(VLI2->VLI_value);

    int carry_flag = NO_CARRY;
    int temp_sum;

    vli_t *smaller_length_VLI;
    vli_t *bigger_length_VLI;

    if (VLI1_length > VLI2_length)
    {
        bigger_length_VLI = VLI1;
        bigger_length_VLI->VLI_value = strrev(VLI1->VLI_value);

        smaller_length_VLI = VLI2;
        smaller_length_VLI->VLI_value = strrev(VLI2->VLI_value);
    }
    else
    {
        bigger_length_VLI = VLI2;
        bigger_length_VLI->VLI_value = strrev(VLI2->VLI_value);

        smaller_length_VLI = VLI1;
        smaller_length_VLI->VLI_value = strrev(VLI1->VLI_value);
    }

    size_t smaller_length = strlen(smaller_length_VLI->VLI_value);
    size_t bigger_length = strlen(bigger_length_VLI->VLI_value);

    sum = (vli_t *)malloc(sizeof(vli_t));
    sum->VLI_value = (char *)malloc(sizeof(char) * (strlen(bigger_length_VLI->VLI_value) + 2));

    int i;
    int second_term;
    int first_term;

    for (i = 0; i < bigger_length; i++)
    {
        first_term = convertASCIIToInt(bigger_length_VLI->VLI_value[i]);
        second_term = (i >= smaller_length) ? 0 : convertASCIIToInt(smaller_length_VLI->VLI_value[i]);

        temp_sum = first_term + second_term + carry_flag;

        if (temp_sum >= BASE_10)
        {
            temp_sum -= BASE_10;
            carry_flag = CARRY;
        }
        else
        {
            carry_flag = NO_CARRY;
        }

        sum->VLI_value[i] = convertIntToASCII(temp_sum);
    }

    if (carry_flag)
    {
        sum->VLI_value[i] = convertIntToASCII(1);
        i++;
    }
    sum->VLI_value[i] = '\0';
    sum->VLI_value = strrev(sum->VLI_value);

    return sum;
}

int convertASCIIToInt(char c)
{
    return c - 48;
}

char convertIntToASCII(int i)
{
    return i + 48;
}