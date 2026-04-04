#include <stdio.h>
#include <stdlib.h>
/* #include <string.h> */
/* #include <sys/stat.h> */

#include "../dstring.h"

/* #define stat struct stat */


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


void init_file_lines(const char *file_name, char **file_lines, int size)
{
    FILE *file;
    int cnt, i;
    char ch;

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
        file_lines[cnt] = malloc(i);
        i = 0;
        cnt++;
    }
    fclose(file);

    file = fopen(file_name, "r");
    if (file == NULL)
        exit(1);
    i = 0;
    cnt = 0;
    while ((ch = fgetc(file)) != EOF) {
        if (ch != '\n') {
            file_lines[cnt][i] = ch;
            continue;
        }
        i = 0;
        cnt++;
    }
    fclose(file);
}


void sort_lines_plain_to_file(
        const char *file_name,
        char **file_lines,
        int cnt_lines,
        int reversed
)
{
    /* ... */
}


void sort_lines_lex_to_file(
        const char *file_name,
        char **file_lines,
        int cnt_lines,
        int reversed
)
{
    /* ... */
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
    file_lines = malloc(cnt_lines);
    init_file_lines(in_file_name, file_lines, cnt_lines);

    if (cmp_cstr(sorting_type, "plain"))
        sort_lines_plain_to_file(out_file_name, file_lines, cnt_lines, 0);
    else if (cmp_cstr(sorting_type, "lex"))
        sort_lines_lex_to_file(out_file_name, file_lines, cnt_lines, 0);
    else if (cmp_cstr(sorting_type, "rplain"))
        sort_lines_plain_to_file(out_file_name, file_lines, cnt_lines, 1);
    else if (cmp_cstr(sorting_type, "rlex"))
        sort_lines_lex_to_file(out_file_name, file_lines, cnt_lines, 1);

    return 0;
}

