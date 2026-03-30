#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int round_div(int x, int y)
{
    if (x % y != 0)
        return x / y + 1;
    return x / y;
}


int cstr_to_int(char *cstring)
{
    int i, res = 0;
    for (i = 0; cstring[i] != '\0'; i++)    
        res = res * 10 + (cstring[i] + '0');
    return res;
}


typedef struct {
    int *array;
    int size, left, right;
} entry;

void init_entry(entry *_entry, int *array, int left, int right)
{
    _entry->array = array;
    _entry->left = left;
    _entry->right = right;
}


void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}


void print_array(int *arr, int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    putchar(10);
}


void *bubble_sort(void *args)
{
    entry *entry_args = (entry*)args;
    int *arr = entry_args->array;
    int i, j, left = entry_args->left, right = entry_args->right;
    for (i = left; i < right; i++)
        for (j = left; j < right + left - i; j++)
            if (arr[j] > arr[j + 1])
                swap(arr + j, arr + j + 1);
    return NULL;
}


int main(int argc, char *argv[])
{
    int size = 10, i, threads_amount, entries_amount;
    int *array = malloc(sizeof(int) * size);
    for (i = 0; i < size; i++)
        array[i] = size - i;
    print_array(array, size);

    if (argc > 1)
        threads_amount = cstr_to_int(argv[1]);
    else
        threads_amount = 1;
    entries_amount = round_div(size, (size - threads_amount + 1));
    pthread_t *threads = malloc(sizeof(pthread_t) * threads_amount);
    entry *entries = malloc(sizeof(entry) * threads_amount);
    for (i = 0; i < threads_amount && i < entries_amount; i++) {
        init_entry(entries + i, array, 0, size);
        pthread_create(threads + i, NULL, bubble_sort, (void*)(entries + i));
    }

    pthread_join(threads[0], NULL);

    print_array(array, size);
    free(array);
    free(threads);
    free(entries);

    return 0;
}

