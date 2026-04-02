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
    int status = mkfifo(fifo_name, 0666);

    int fifo_stream, write_flag = 1;
    fifo_stream = open(fifo_name, O_WRONLY | O_NONBLOCK, 0666);  
    if (fifo_stream == -1) {
        fifo_stream = open(fifo_name, O_RDONLY, 0666);
        write_flag = 0;
    } else {
        close(fifo_stream);
        fifo_stream = open(fifo_name, O_WRONLY, 0666);
    }
 
    const int input_size = 1024;
    const int output_size = 1024;
    int read_status, write_status;
    char input[input_size] = {};
    char output[output_size] = {};

    if (write_flag) {
        printf(">");
        fgets(input, input_size, stdin);
        input[find_symb_cstr(input, '\n')] = '\0';
        write_status = write(fifo_stream, input, input_size);
        printf("Write %d bytes\n", write_status);
    } else {
        read_status = read(fifo_stream, output, output_size);
        printf("Read %d bytes\n< %s\n", read_status, output);
    } 
 

    return 0;
}



