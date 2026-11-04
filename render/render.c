#include "render.h"

int get_render_char_length(uchar c)
{
    if ((c & 128) == 0) return 1;
    if ((c & 224) == 192) return 2;
    if ((c & 240) == 224) return 3;
    if ((c & 248) == 240) return 4;
    return -1;
}


void render(int start_x, int start_y, int largura, int lins, uchar* text, int offset)
{
    char buffer[6767] = {0};
    size_t buffer_pos = 0;
    buffer_pos += sprintf(buffer + buffer_pos, "\033[?25l");

    int text_len = text ? strlen((char*)text) : 0;
    int text_pos = 0;

    for (int lin = 1; lin <= lins; lin++) {
        buffer_pos += sprintf(buffer + buffer_pos, "\033[%d;%dH%s", start_y + lin, start_x, "| ");
        int col = 0;
        int offset_counter = 0;
        
        while (text_pos < text_len && text[text_pos] != '\n' && col < largura) {
            int length = get_render_char_length(text[text_pos]);
            while (text_pos < text_len && length == -1) length = get_render_char_length(text[++text_pos]);
            if (text[text_pos] == '\n') break;    

            if (offset_counter >= offset){
                buffer[buffer_pos++] = text[text_pos];
                while (length-- > 1) buffer[buffer_pos++] = text[++text_pos];
                col++;
            }
            else{
                offset_counter++;
            }
   
            text_pos++;
        }

        while (text_pos < text_len && text[text_pos] != '\n') text_pos++;
        if (text_pos < text_len && text[text_pos] == '\n') text_pos++;
        
        while (col < largura) {
            buffer[buffer_pos++] = ' ';
            col++;
        }

        
        //buffer_pos += sprintf(buffer + buffer_pos, "%s", " |");
    }

    sprintf(buffer + buffer_pos, "\033[?25h");
    printf("%s", buffer);
    fflush(stdout);
}


void render_buffer(buffer_renderer* info){
    uchar* text = get_text(*(info->gap_buffer));

    render(info->posx, info->posy, info->sizex, info->sizey, text, info->offset);
}