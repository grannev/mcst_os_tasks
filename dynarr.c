#include "dynarr.h"

void init_dynarr(dynarr *this)
{
    this->size = 0;
    this->array = NULL;
}

void expand_dynarr(dynarr *this, int size)
{
    size += this->size;
    int *new_arr = malloc(sizeof(int) * size);

    int i;
    for (i = 0; i < size; i++)
        if (i < this->size)
            new_arr[i] = this->array[i];
        else
            new_arr[i] = 0;

    free(this->array);
    this->array = new_arr;
    this->size = size;
}

void push_back_dynarr(dynarr *this, int val)
{
    expand_dynarr(this, 1);
    this->array[this->size - 1] = val;
}


