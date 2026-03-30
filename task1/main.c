#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}


void *bubble_sort(int *arr, int left, int right)
{
    int i, j;
    for (i = left; i < right; i++)
        for (j = left; j < right - i; j++)
            if (arr[j] > arr[j + 1])
                swap(arr + j, arr + j + 1);
    return NULL;
}


void print_array(int *arr, int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    putchar(10);
}


int main(int argc, char *argv[])
{
    int size = 10, i;
    int *array = malloc(sizeof(int) * size);
    for (i = 0; i < size; i++)
        array[i] = size - i;

    print_array(array, size);
    bubble_sort(array, 0, size);
    print_array(array, size);

    free(array);

    return 0;
}

