#ifndef VLI_READER_H_
#define VLI_READER_H_

typedef struct VLI
{
    int isNegative;
    char *VLI_value;
} vli_t;

vli_t *readVLI(char *Path);

#endif