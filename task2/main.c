#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include "../dstring.h"


int main(int argc, char *argv[])
{
    /* name of fifo file from arguments */
    const char *fifo_name = argv[1];

    /* buffers size */
    const int input_size = 1024;
    const int output_size = 1024;
    
    /* i-node of fifo file */
    int fifo_stream;

    /* status of what we need to do now with stream */
    int write_flag;

    /* buffers for data */
    char *input = malloc(input_size);
    char *output = malloc(input_size);

    if (argc < 2)
        return 1;

    mkfifo(fifo_name, 0666); /* creating fifo if user doesnt */

    write_flag = 1;
    fifo_stream = open(fifo_name, O_WRONLY | O_NONBLOCK, 0666);  
    /* if no one open to read, returns -1 */
    if (fifo_stream == -1) {
        fifo_stream = open(fifo_name, O_RDONLY, 0666);
        write_flag = 0;
    } else {
        close(fifo_stream);
        fifo_stream = open(fifo_name, O_WRONLY, 0666);
    }

    /* According to write_flag chosing what action we need to do now,
     * after reading or writing data, close fifo_stream and
     * open for read or write respectively */
    while (!cmp_cstr(input, "--quit")) {
        if (write_flag) {
            /*printf("<"); */
            fgets(input, input_size, stdin);
            input[find_symb_cstr(input, '\n')] = '\0';
            write(fifo_stream, input, input_size);
        } else {
            read(fifo_stream, output, output_size);
            /*printf(">"); */
            printf("%s\n", output);
        }
        clr_cstr(input);
        clr_cstr(output);
        close(fifo_stream);
        write_flag = !write_flag;
        if (write_flag)
            fifo_stream = open(fifo_name, O_WRONLY, 0666);
        else
            fifo_stream = open(fifo_name, O_RDONLY, 0666);
    }

    free(input);
    free(output);
    return 0;
}



