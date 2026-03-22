#include <stdio.h>
#include "serial.h"

#define DEV_PATH "/dev/ttyACM0"

int main(void)
{
    int fd = serial_open(DEV_PATH);
    if (fd < 0)
        return -1;

    if (serial_config(fd) < 0)
    {
        serial_close(fd);
        return -1;
    }

    printf("serial open success\n");

    char buf[64];

    while (1)
    {
        int n = serial_read_data(fd, buf, sizeof(buf) - 1);
        if (n > 0)
        {
            buf[n] = '\0';
            //printf("%d\n",n);
            printf("%s", buf);
        }
    }

    serial_close(fd);
    return 0;
}