#include <stdio.h>
#include "serial.h"
#include "protocol.h"

#define DEV_PATH "/dev/ttyACM1"

int main(void)
{
    int fd = serial_open(DEV_PATH);
    if (fd < 0)
    {
        printf("serial open failed\n");
        return -1;
    }

    if (serial_config(fd) < 0)
    {
        printf("serial config failed\n");
        serial_close(fd);
        return -1;
    }

    printf("serial open and config success\n");

    frame_parser parser;
    if (Frame_Reset(&parser) < 0)
    {
        printf("frame reset failed\n");
        serial_close(fd);
        return -1;
    }

    char rxbuf[64];

    while (1)
    {
        int n = serial_read_data(fd, rxbuf, sizeof(rxbuf));
        if (n < 0)
        {
            printf("serial read failed\n");
            break;
        }

        for (int i = 0; i < n; i++)
        {
            int ret = Frame_Feed(&parser, rxbuf[i]);

            if (ret == 1)
            {
                float tem = 0.0f;
                float hum = 0.0f;

                printf("完整帧: %s\n", parser.buf);

                if (Parse_Data_Frame(parser.buf, &tem, &hum) == 0)
                {
                    printf("温度: %.2f, 湿度: %.2f\n", tem, hum);
                }
                else
                {
                    printf("解析失败: %s\n", parser.buf);
                }
            }
            else if (ret == -1)
            {
                printf("组帧错误\n");
            }
        }
    }

    serial_close(fd);
    return 0;
}