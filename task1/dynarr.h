#ifndef DYNARR_HEADER
#define DYNARR_HEADER

#include <stdlib.h>

typedef struct {
    int *array;
    int size;
} dynarr;

void init_dynarr(dynarr *this);
void expand_dynarr(dynarr *this, int size);
void push_back_dynarr(dynarr *this, int val);

#endif

