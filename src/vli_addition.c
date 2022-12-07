#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "vli_reader.h"

#define ASCII_OFFSET 48

vli_t *addVLIs(vli_t *VLI1, vli_t *VLI2);
char convertIntToASCII(int i);
int convertASCIIToInt(char c);

vli_t *addVLIs(vli_t *VLI1, vli_t *VLI2)
{
    vli_t *sum = NULL;
    size_t VLI1_length = strlen(VLI1->VLI_value);
    size_t VLI2_length = strlen(VLI2->VLI_value);

    int carry_flag = 0;
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
    int polarity = (VLI1->isNegative == VLI2->isNegative) ? 1 : -1;

    for (i = 0; i < bigger_length; i++)
    {
        first_term = convertASCIIToInt(bigger_length_VLI->VLI_value[i]);
        second_term = (i >= smaller_length) ? 0 : convertASCIIToInt(smaller_length_VLI->VLI_value[i]);

        if (polarity == -1)
        {
            first_term = (bigger_length_VLI->isNegative) ? first_term * -1 : first_term;
            second_term = (smaller_length_VLI->isNegative) ? second_term * -1 : second_term;
        }

        temp_sum = first_term + second_term + carry_flag;

        if (temp_sum >= 10)
        {
            temp_sum -= 10;
            carry_flag = 1;
        }
        else if (temp_sum > 0 && temp_sum < 10)
        {
            carry_flag = 0;
        }
        else
        {
            temp_sum += 10;
            carry_flag = -1;
        }

        sum->VLI_value[i] = convertIntToASCII(temp_sum);
    }

    if (carry_flag != 0)
    {
        sum->VLI_value[i] = convertIntToASCII(1);
        i++;
    }
    sum->isNegative = (carry_flag == -1) ? 1 : 0;
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