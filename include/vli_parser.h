#ifndef VLI_READER_H_
#define VLI_READER_H_

#define NEGATIVE 1
#define POSITIVE 0

typedef struct VLI
{
    int isNegative;
    char *VLI_value;
    int length;
} vli_t;

vli_t *normalizeVLI(vli_t *VLI);
char convertIntToASCII(int i);
int convertASCIIToInt(char c);
vli_t *readVLI(char *Path);

#endif