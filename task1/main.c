#include <stdio.h>
#include <pthread.h>

#include "../dynarr.h"


int round_div(int x, int y)
{
    if (x % y != 0)
        return x / y + 1;
    return x / y;
}


int cstr_to_int(char *cstring)
{
    int i, res = cstring[0] - '0';
    for (i = 1; cstring[i] != '\0'; i++)    
        res = res * 10 + (cstring[i] - '0');
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


/* todo: make it in threads... */
void merge(int *array, int left, int mid, int right)
{
    int n = mid - left + 1, m =  right - mid, i, j, k;
    int *pleft = malloc(sizeof(int) * n);
    int *pright = malloc(sizeof(int) * m);

    for (i = 0; i < n; i++)
        pleft[i] = array[left + i];
    for (i = 0; i < m; i++)
        pright[i] = array[mid + i + 1];

    i = 0;
    j = 0;
    k = left;
    while (i < n && j < m) {
        if (pleft[i] <= pright[j])
            array[k++] = pleft[i++];
        else
            array[k++] = pright[j++];
    }
    while (i < n)
        array[k++] = pleft[i++];
    while (j < m)
        array[k++] = pright[j++];

    free(pleft);
    free(pright);
}


int main(int argc, char *argv[])
{
    int threads_amount = cstr_to_int(argv[1]);
    int part_size, i, left, mid, right, curr, tmp, size;

    if (argc < 2)
        return 1;
    
    /* init array */
    dynarr dyn;
    init_dynarr(&dyn);
    while (scanf("%d", &tmp) == 1)
        push_back_dynarr(&dyn, tmp);
    size = dyn.size;

    /* init threads */
    part_size = (size + threads_amount - 1) / threads_amount;
    pthread_t *threads = malloc(sizeof(pthread_t) * threads_amount);
    entry *entries = malloc(sizeof(entry) * threads_amount);
    for (i = 0; i < threads_amount; i++) {
        /* spliting array on parts according to amount of threads */
        /* extra threads will not be used */
        /* for example: for array of 10 elements */
        /* we can use no more than 5 threads because of */
        /* 10 / 5 = 2 its smallest array that we can sort */
        /* so we gonna split array on 5 parts, sort it in each thread */
        /* and then merge it */
        left = i * part_size;
        right = (i + 1) * part_size - 1;
        if (right >= size)
            right = size - 1;
        if (left >= size)
            continue;
        init_entry(entries + i, dyn.array, left, right);
        pthread_create(threads + i, NULL, bubble_sort, (void*)(entries + i));
    }

    /* wait for threads */
    for (i = 0; i < threads_amount; i++)
        if (i * part_size < size)
            pthread_join(threads[i], NULL);
   
    /* merge sorted parts */
    for (curr = part_size; curr < size; curr *= 2) {
        for (left = 0; left < size; left += 2*curr) {
            mid = left + curr - 1;
            tmp = left + 2 * curr - 1;
            right = tmp < size ? tmp : size - 1;
            if (mid < right)
                merge(dyn.array, left, mid, right);
        }
    }
    
    print_array(dyn.array, size);
    
    free(dyn.array);
    free(threads);
    free(entries);

    return 0;
}

