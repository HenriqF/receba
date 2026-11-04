#ifndef RENDER
#define RENDER

#include <stdio.h>
#include "../gapbuffer.h"
#define uchar unsigned char

typedef struct {
    int posx, posy, sizex, sizey;
    int offset;

    GapBuffer* gap_buffer;
} buffer_renderer;


void render_buffer(buffer_renderer* tc);

#endif