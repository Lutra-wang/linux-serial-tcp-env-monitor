#include <stdio.h>
#include <string.h>

#include "serial.h"
#include "protocol.h"
#include "tcp_server.h"

#define DEV_PATH "/dev/ttyACM0"
#define TCP_PORT 8888

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

    int server_fd = tcp_server_init(TCP_PORT);
    if (server_fd < 0)
    {
        printf("tcp server init failed\n");
        serial_close(fd);
        return -1;
    }

    printf("tcp server listening on port %d\n", TCP_PORT);

    int client_fd = tcp_server_accept(server_fd);
    if (client_fd < 0)
    {
        tcp_server_close(server_fd);
        serial_close(fd);
        return -1;
    }

    frame_parser parser;
    if (Frame_Reset(&parser) < 0)
    {
        printf("frame reset failed\n");
        tcp_server_close(client_fd);
        tcp_server_close(server_fd);
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

                    char send_buf[128];
                    int len = snprintf(send_buf, sizeof(send_buf),
                                       "TEMP=%.2f,HUM=%.2f\n", tem, hum);

                    if (tcp_server_send(client_fd, send_buf, len) < 0)
                    {
                        printf("client disconnected or send failed\n");
                        goto exit_loop;
                    }
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

exit_loop:
    tcp_server_close(client_fd);
    tcp_server_close(server_fd);
    serial_close(fd);
    return 0;
}