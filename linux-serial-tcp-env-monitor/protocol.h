#ifndef _PROTOCOL_H_
#define _PROTOCOL_H_

#define FRAME_MAX_LEN 128 

typedef enum
{
    WAIT_HEAD_FRAME = 0,
    ACCEPT_DATA_FRAME = 1
}frame_state;

typedef struct
{
    frame_state state;
    char buf[FRAME_MAX_LEN];
    int size;
}frame_parser;

int Frame_Reset(frame_parser *p);

int Frame_Feed(frame_parser *p,char ch);

int Parse_Data_Frame(const char *frame, int *value);

#endif