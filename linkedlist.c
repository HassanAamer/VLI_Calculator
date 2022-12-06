#include <stdio.h>
#include <stdlib.h>

typedef struct Place
{
    int value;
    struct Place *nextPlace;
} place_t;

int add_left(place_t *numberRight, place_t *numberLeft, int add_value)
{
    place_t *new = (place_t *)malloc(sizeof(place_t));
    if (new == NULL)
    {
        return 1;
    }
    new->value = add_value;

    if (numberRight == NULL)
    {
        numberRight = new;
        numberLeft = new;
        new->nextPlace = NULL;
    }
    else
    {
        numberLeft->nextPlace = new;
        numberLeft = new;
    }

    return 0;
}