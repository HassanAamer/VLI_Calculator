#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "vli_parser.h"

#define ASCII_OFFSET 48
#define NO_CARRY 0
#define BASE_10 10
#define CARRY 1

vli_t *addSignedVLIs(vli_t *VLI1, vli_t *VLI2);
vli_t *addUnsignedVLIs(vli_t *biggerVLI, vli_t *smallerVLI, vli_t *sum);
vli_t *subtractVLIs(vli_t *minuend, vli_t *subtractend, vli_t *output);
int isGreaterThan(vli_t *VLI1, vli_t *VLI2);

/*
    This function takes two signed VLI's as input and returns
    the signed sum.
 */
vli_t *addSignedVLIs(vli_t *VLI1, vli_t *VLI2)
{
    vli_t *bigger_VLI = NULL;
    vli_t *smaller_VLI = NULL;

    if (isGreaterThan(VLI1, VLI2))
    {
        bigger_VLI = VLI1;
        smaller_VLI = VLI2;
    }
    else
    {
        bigger_VLI = VLI2;
        smaller_VLI = VLI1;
    }

    vli_t *sum = (vli_t *)malloc(sizeof(vli_t));
    sum->VLI_value = (char *)malloc(sizeof(char) * (strlen(bigger_VLI->VLI_value) + 2));

    if (bigger_VLI->isNegative != smaller_VLI->isNegative)
    {
        // If both VLI's have different signs, the sum has the sign of the
        // larger VLI
        sum = subtractVLIs(bigger_VLI, smaller_VLI, sum);
        sum->isNegative = (bigger_VLI->isNegative) ? NEGATIVE : POSITIVE;
    }
    else
    {
        // If both VLI's have the same sign, the sum has the sign of one of
        // the VLI's
        sum = addUnsignedVLIs(bigger_VLI, smaller_VLI, sum);
        sum->isNegative = bigger_VLI->isNegative;
    }

    return normalizeVLI(sum);
}

vli_t *subtractVLIs(vli_t *minuend, vli_t *subtractend, vli_t *output)
{
    size_t minuend_length = strlen(minuend->VLI_value);
    size_t subtractend_length = strlen(subtractend->VLI_value);

    char *minuend_value = strrev(minuend->VLI_value);
    char *subtractend_value = strrev(subtractend->VLI_value);

    int bottom_term, top_term;
    int result;
    int isBorrowing = false;
    int i = 0;

    for (i = 0; i < minuend_length; i++)
    {
        top_term = convertASCIIToInt(minuend_value[i]);
        if (isBorrowing && (top_term == 0))
        {
            // Borrowing has not been satisfied, it cascades, zero becomes nine
            isBorrowing = true;
            top_term = BASE_10 - 1;
        }
        else if (isBorrowing)
        {
            // Borrowing has been satisfied, take from non-zero number
            top_term = top_term - 1;
            isBorrowing = false;
        }
        bottom_term = (i >= subtractend_length) ? 0 : convertASCIIToInt(subtractend_value[i]);

        result = top_term - bottom_term;

        if (result < 0)
        {
            // Need to borrow
            isBorrowing = true;
            result += BASE_10;
        }

        output->VLI_value[i] = convertIntToASCII(result);
    }

    // Null-terminate string
    output->VLI_value[i] = '\0';
    output->VLI_value = strrev(output->VLI_value);

    return output;
}

vli_t *addUnsignedVLIs(vli_t *biggerVLI, vli_t *smallerVLI, vli_t *sum)
{
    size_t bigger_length = strlen(biggerVLI->VLI_value);
    char *bigger_value = strrev(biggerVLI->VLI_value);

    size_t smaller_length = strlen(smallerVLI->VLI_value);
    char *smaller_value = strrev(smallerVLI->VLI_value);

    int carry_flag = NO_CARRY;
    int temp_sum;

    int i;
    int second_term;
    int first_term;

    for (i = 0; i < bigger_length; i++)
    {
        first_term = convertASCIIToInt(bigger_value[i]);
        second_term = (i >= smaller_length) ? 0 : convertASCIIToInt(smaller_value[i]);

        temp_sum = first_term + second_term + carry_flag;

        if (temp_sum >= BASE_10)
        {
            // Write only right-most digit, carry
            temp_sum -= BASE_10;
            carry_flag = CARRY;
        }
        else
        {
            // Carrying stops
            carry_flag = NO_CARRY;
        }

        sum->VLI_value[i] = convertIntToASCII(temp_sum);
    }

    if (carry_flag)
    {
        // Write an extra 1
        sum->VLI_value[i] = convertIntToASCII(1);
        i++;
    }
    sum->VLI_value[i] = '\0';
    sum->VLI_value = strrev(sum->VLI_value);

    return sum;
}

int isGreaterThan(vli_t *VLI1, vli_t *VLI2)
{
    /*
        This function takes as input two VLI's and returns 1 if VLI1 is greater
        than VLI2, 0 otherwise.
     */
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
