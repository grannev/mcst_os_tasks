#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#include "dstring.h"


int main(int argc, char *argv[])
{
    if (argc < 2)
        return 1;

    const char *fifo_name = argv[1];
    mkfifo(fifo_name, 0666); // creating fifo if user doesnt

    int fifo_stream, write_flag = 1;
    fifo_stream = open(fifo_name, O_WRONLY | O_NONBLOCK, 0666);  
    // if no one open to read, returns -1
    if (fifo_stream == -1) {
        fifo_stream = open(fifo_name, O_RDONLY, 0666);
        write_flag = 0;
    } else {
        close(fifo_stream);
        fifo_stream = open(fifo_name, O_WRONLY, 0666);
    }

    // buffers for data
    const int input_size = 1024;
    const int output_size = 1024;
    char input[input_size] = {};
    char output[output_size] = {};
    
    /* According to write_flag chosing what action we need to do now,
     * after reading or writing data, close fifo_stream and
     * open for read or write respectively */
    while (!cmp_cstr(input, "--quit")) {
        if (write_flag) {
            //printf("<");
            fgets(input, input_size, stdin);
            input[find_symb_cstr(input, '\n')] = '\0';
            write(fifo_stream, input, input_size);
        } else {
            read(fifo_stream, output, output_size);
            //printf(">");
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

    return 0;
}



