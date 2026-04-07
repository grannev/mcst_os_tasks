#include <stdio.h>
#include <stdlib.h>
/* #include <string.h> */
/* #include <sys/stat.h> */

#include "../dstring.h"

/* #define stat struct stat */


void swap_value(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}


/* read data from file by his name and counts number of '\n' chars */
int cnt_lines_file(const char *file_name)
{
    FILE *file;
    char buffer[256];
    int result;

    file = fopen(file_name, "r");
    if (file == NULL)
        return 1;

    result = 0;
    while (fgets(buffer, sizeof(buffer), file)) {
        result += cnt_char_cstr(buffer, '\n');
        if (buffer[0] == '\n')
            result--;
    }

    fclose(file);
    return result;
}


/* read data from file and malloc exact size for each line of file */
void init_file_lines(const char *file_name, char **file_lines, int size)
{
    FILE *file;
    int cnt, i;
    char ch;

    /* in cycle malloc specific memory for each line */
    file = fopen(file_name, "r");
    if (file == NULL)
        exit(1);
    i = 0;
    cnt = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch != '\n') {
            i++;
            continue;
        }
        if (i == 0)
            continue;
        file_lines[cnt] = malloc(i);
        i = 0;
        cnt++;
    }
    fclose(file);

    /* read data in allocated memory parts from corresponding lines */
    file = fopen(file_name, "r");
    if (file == NULL)
        exit(1);
    i = 0;
    cnt = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch != '\n') {
            file_lines[cnt][i] = ch;
            i++;
            continue;
        }
        if (i == 0)
            continue;
        i = 0;
        cnt++;
    }
    fclose(file);
}


/* free allocated memory */
void free_file_lines(char **file_lines, int size)
{
    int i;
    for (i = 0; i < size; i++)
        free(file_lines[i]);
    free(file_lines);
}


/* sorting array of numbers, that describe  */ 
/* indeces of lines in cstrings array       */
/* and then according to indeces in array   */ 
/* of nums write corresponding cstr to file */
void sort_lines_plain_to_file(
        const char *file_name,
        char **file_lines,
        int cnt_lines,
        int reversed
)
{
    int i, j;
    int *indices = malloc(sizeof(int) * cnt_lines);
    FILE *file;

    /* init indices */
    for (i = 0; i < cnt_lines; i++)
        indices[i] = i;
   
    /* using bubble sort */
    for (i = 0; i + 1 < cnt_lines; i++)
        for (j = 0; j + 1 < cnt_lines - i; j++)
            if (!reversed) {
                if (cmp_cstr_plain(
                            file_lines[indices[j + 1]], 
                            file_lines[indices[j]]
                    ))
                    swap_value(indices + j + 1, indices + j);
            } else {
                if (cmp_cstr_plain(
                            file_lines[indices[j]],
                            file_lines[indices[j + 1]] 
                    ))
                    swap_value(indices + j + 1, indices + j);
            }
   
    /* write our data */
    file = fopen(file_name, "w");
    for (i = 0; i < cnt_lines; i++) {
        fputs(file_lines[indices[i]], file);
        fputc(10, file);
    }

    fclose(file);
    free(indices);
}


/* do the same way like previous but sorting is lex */
void sort_lines_lex_to_file(
        const char *file_name,
        char **file_lines,
        int cnt_lines,
        int reversed
)
{
    int i, j;
    int *indices = malloc(sizeof(int) * cnt_lines);
    FILE *file;

    for (i = 0; i < cnt_lines; i++)
        indices[i] = i;
   
    for (i = 0; i + 1 < cnt_lines; i++)
        for (j = 0; j + 1 < cnt_lines - i; j++)
            if (!reversed) {
                if (cmp_cstr_lex(
                            file_lines[indices[j + 1]], 
                            file_lines[indices[j]]
                    ))
                    swap_value(indices + j + 1, indices + j);
            } else {
                if (cmp_cstr_lex(
                            file_lines[indices[j]],
                            file_lines[indices[j + 1]] 
                    ))
                    swap_value(indices + j, indices + j + 1);
            }

    file = fopen(file_name, "w");
    for (i = 0; i < cnt_lines; i++) {
        fputs(file_lines[indices[i]], file);
        fputc(10, file);
    }

    fclose(file);
    free(indices);
}


int main(int argc, char **argv)
{
    const char *in_file_name;
    const char *out_file_name;
    const char *sorting_type;
    int cnt_lines;
    char **file_lines;
    
    if (argc < 4)
        return 1;
    
    in_file_name = argv[1];
    out_file_name = argv[2];
    sorting_type = argv[3];

    cnt_lines = cnt_lines_file(in_file_name);
    file_lines = malloc(sizeof(char*) * cnt_lines);
    init_file_lines(in_file_name, file_lines, cnt_lines);

    /* chose what sort we need */
    if (cmp_cstr(sorting_type, "plain"))
        sort_lines_plain_to_file(out_file_name, file_lines, cnt_lines, 0);
    else if (cmp_cstr(sorting_type, "lex"))
        sort_lines_lex_to_file(out_file_name, file_lines, cnt_lines, 0);
    else if (cmp_cstr(sorting_type, "rplain"))
        sort_lines_plain_to_file(out_file_name, file_lines, cnt_lines, 1);
    else if (cmp_cstr(sorting_type, "rlex"))
        sort_lines_lex_to_file(out_file_name, file_lines, cnt_lines, 1);

    free_file_lines(file_lines, cnt_lines);
    return 0;
}

