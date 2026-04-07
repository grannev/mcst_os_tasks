#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>


/* didnt find how to get a depricated sys_errlist[] and dont */
/* have much time to static compile old versions of libc */
/* so use only perror */


const char *get_errname(int code)
{
    switch (code) {
        case 2: return "ENOENT";
        case 13: return "EACCESS";
        case 21: return "EISDIR";
        case 26: return "ETXTBSY";
    }
    return "EUNKNOWN";
}


int main(void)
{
    int file;

    file = open("null-file.txt", O_RDWR, 0666);
    if (file == -1) {
        perror("Can't open file null-file.txt");
        printf("Errno = %s\n\n", get_errname(errno));
    }

    file = open("dir", O_RDWR);
    if (file == -1) {
        perror("Can't open file dir");
        printf("Errno = %s\n\n", get_errname(errno));
    }

    file = open("/bin/gcc", O_WRONLY);
    if (file == -1) {
        perror("Can't open file /bin/gcc");
        printf("Errno = %s\n\n", get_errname(errno));
    }

    file = open("task5", O_WRONLY);
    if (file == -1) {
        perror("Can't open file task5");
        printf("Errno = %s\n\n", get_errname(errno));
    }

    return 0;
}

