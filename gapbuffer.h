#ifndef GAPBUFFER
#define GAPBUFFER

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GBRED "\x1b[31m"
#define GBRESET "\x1b[0m"

#define uchar unsigned char


typedef struct{
    uchar* buffer;
    size_t buffer_size;
    size_t gap_size; //const

    size_t gapl; //index gapleft
    size_t gapr; //gapright
} GapBuffer;

typedef struct {
    uchar* text;
    size_t text_size;
    size_t cursor_index;
    int ok;
} TextExchange;


//off
void init_gb(GapBuffer* gb, size_t gap_size);
uchar* get_text(GapBuffer gb);
void get_textexchange(GapBuffer gb, TextExchange* te);

//grow
void grow(GapBuffer* gb);

//insert, delete
void insert_string(GapBuffer* gb, uchar* string, size_t len);
void insert_char(GapBuffer* gb, uchar c);
void delete_char(GapBuffer* gb);

//movingfs
void move_left(GapBuffer* gb);
void move_right(GapBuffer* gb);
#endif