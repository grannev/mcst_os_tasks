#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sysmacros.h>
#include <fcntl.h>
#include <unistd.h>


/* using std macros place corresponding file type */
const char *place_file_type(mode_t file_mode)
{
    if (S_ISREG(file_mode))
        return "regular file";
    else if (S_ISDIR(file_mode))
        return "directory";
    else if (S_ISLNK(file_mode))
        return "symbolic link";
    return "unknown";
}


/* compare array of macro bytes with out file_mode */
/* and place an access char to stdout */
/* form array of digital number of access rights */
/* same way and then printing it */
/* void print_access(mode_t file_mode) */
{ 
    const int chb[9] = {
        S_IRUSR, S_IWUSR, S_IXUSR,
        S_IRGRP, S_IWGRP, S_IXGRP,
        S_IROTH, S_IWOTH, S_IXOTH
    };
    const int  dgb[3] = {4, 2, 1};
    const char plb[3] = {'r', 'w', 'x'};

    int i, j;
    int digital[3] = {0, 0, 0};
    char ch;

    ch = place_file_type(file_mode)[0];
    if (ch == 'd')
        putchar(ch);
    else
        putchar('-');

    for (i = 0, j = -1; i < 9; i++) {
        if (i % 3 == 0)
            j++;
        if (file_mode & chb[i]) {
            putchar(plb[i % 3]);
            digital[j] += dgb[i % 3];
        } else {
            putchar('-');
        }
    }

    printf("/0");
    for (i = 0; i < 3; i++)
        putchar(digital[i] + '0');

    putchar(10);
}


void print_file_stat(const char *file_name)
{
    struct stat file_stat;
    mode_t file_mode;
    int status;

    status = stat(file_name, &file_stat);
    if (status == -1) {
        perror("stat: cannot statx file");
        exit(1);
    }
    file_mode = file_stat.st_mode;
   
    /* trying to make format of data like in stat */
    printf("  File: %s\n", file_name);
    printf("%2cSize: %lu", ' ', file_stat.st_size);
    printf("%4cBlocks: %lu", ' ', file_stat.st_blocks);
    printf("%4cIO Block: %lu", ' ', file_stat.st_blksize);
    printf("%4c%s\n", ' ', place_file_type(file_mode));
    printf("Device: %u,%u",  major(file_stat.st_dev), 
                             minor(file_stat.st_dev));
    printf("%4cInode: %lu", ' ', file_stat.st_ino);
    printf("%4cLinks: %lu\n", ' ', file_stat.st_nlink);
    printf("Access: "); print_access(file_mode);
    /* todo: time of access/modify/change/birth */
}


int main(int argc, char **argv)
{
    const char *file_name;

    if (argc < 2)
        return 1;
    file_name = argv[1];

    print_file_stat(file_name);

    return 0;
}

