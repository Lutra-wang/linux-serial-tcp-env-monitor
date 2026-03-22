#include <stdio.h>
#include "protocol.h"

void run_test(const char *stream)
{
    frame_parser parser;
    Frame_Reset(&parser);

    printf("测试输入流: %s\n", stream);

    for (int i = 0; stream[i] != '\0'; i++)
    {
        int ret = Frame_Feed(&parser, stream[i]);

        if (ret == 1)
        {
            int value = 0;
            printf("收到完整帧: %s\n", parser.buf);

            if (Parse_Data_Frame(parser.buf, &value) == 0)
            {
                printf("解析成功, value = %d\n", value);
            }
            else
            {
                printf("解析失败\n");
            }
        }
        else if (ret == -1)
        {
            printf("组帧错误\n");
        }
    }

    printf("测试结束\n\n");
}

int main(void)
{
    run_test("$DATA,1#");
    run_test("abc$DATA,2#");
    run_test("$DATA,3#$DATA,4#");
    run_test("xxx$DATA,5#yyy$DATA,6#");
    run_test("$DATA,100#");

    return 0;
}