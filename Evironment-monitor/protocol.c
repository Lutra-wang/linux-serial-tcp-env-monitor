#include "protocol.h"
#include<stdio.h>

int Frame_Reset(frame_parser *p)
{
    if (p == NULL)
    {
        printf("ptr is NULL\n");
        return -1;
    }
    p->state = WAIT_HEAD_FRAME;
    p->size = 0;
    return 0;
}

int Frame_Feed(frame_parser *p,char ch)
{
    if (p == NULL)
    {
        printf("ptr is NULL\n");
        return -1;
    }

    if(p->state == WAIT_HEAD_FRAME)
    {
        if(ch == '$')
        {
            p->size = 0;
            p->state = ACCEPT_DATA_FRAME;
        }
        return 0;
    }
    else if(p->state == ACCEPT_DATA_FRAME)
    {
        if(ch != '#')
        {
            if(p->size >= FRAME_MAX_LEN-1) //±ß½çÎª¡®\0¡¯
            {
                Frame_Reset(p);
                return -1;
            }
            else
            {
                p->buf[p->size++] = ch;
                return 0;
            }
        }
        else 
        {
            p->buf[p->size] = '\0';
            p->state = WAIT_HEAD_FRAME;
            return 1;
        }
    }
    return -1;
}

int Parse_Data_Frame(const char *frame, int *value)
{
    if (frame == NULL || value == NULL)
        return -1;

    if (sscanf(frame, "DATA,%d", value) == 1)
        return 0;

    return -1;
}