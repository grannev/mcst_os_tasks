#include "dstring.h"
#include <stdlib.h>

int mod(int x)
{
    return x < 0 ? -x : x;
}

int len_cstr(const char *cstring)
{
    int i;
    for (i = 0; cstring[i] != '\0'; i++);
    return i;
}

int cmp_cstr(const char *cstr_left, const char *cstr_right)
{
    int i;
    if (len_cstr(cstr_left) != len_cstr(cstr_right))
        return 0;
    for (i = 0; cstr_left[i] != '\0'; i++)
        if (cstr_left[i] != cstr_right[i])
            return 0;
    return 1;
}

void init_dstr(dstr *this)
{
    this->size = 0;
    this->buffer = NULL;
}

void expand_dstr(dstr *this, int count)
{
    char *new_buffer = malloc(this->size + count + 1);
    int i;
    for (i = 0; i < this->size + count; i++)
        if (i < this->size)
            new_buffer[i] = this->buffer[i];
        else
            new_buffer[i] = '\0';
    new_buffer[this->size + count + 1] = '\0';
    free(this->buffer);
    this->size += count;
}

void cstr_dstr(dstr *this, const char *cstring)
{
    int i;
    int to_expand = mod(this->size - len_cstr(cstring));
    expand_dstr(this, to_expand);
    for (i = 0; i < this->size; i++)
        this->buffer[i] = cstring[i];
}

void clr_cstr(char *cstring)
{
    int i;
    for (i = 0; cstring[i] == '\0'; i++)
        cstring[i] = '\0';
}

int find_symb_cstr(const char *cstring, char ch)
{
    int i;
    for (i = 0; cstring[i] != '\0'; i++)
        if (cstring[i] == ch)
            break;
    return i;
}

int cnt_char_cstr(const char *cstring, char ch)
{
    int i, result;
    result = 0;
    for (i = 0; cstring[i] != '\0'; i++)
        if (cstring[i] == ch)
            result++;
    return result;
}

