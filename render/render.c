#include "render.h"

int get_render_char_length(uchar c)
{
    if ((c & 128) == 0) return 1;
    if ((c & 224) == 192) return 2;
    if ((c & 240) == 224) return 3;
    if ((c & 248) == 240) return 4;
    return -1;
}

//void render(int start_x, int start_y, int largura, int lins, uchar* text, int offset)
void render(text_exchange* te, buffer_renderer* info)
{
    char buffer[6767] = {0};
    size_t buffer_pos = 0;
    buffer_pos += sprintf(buffer + buffer_pos, "\033[?25l");

    int text_len = te->text ? strlen((char*)te->text) : 0;
    int text_pos = 0;

    for (int lin = 1; lin <= info->sizey; lin++) {
        buffer_pos += sprintf(buffer + buffer_pos, "\033[%d;%dH%s", info->posy + lin, info->posx, "| ");
        int col = 0;
        int offset_counter = 0;
        
        while (text_pos < text_len && te->text[text_pos] != '\n' && col < info->sizex) {
            int length = get_render_char_length(te->text[text_pos]);
            while (text_pos < text_len && length == -1) length = get_render_char_length(te->text[++text_pos]);
            if (te->text[text_pos] == '\n') break;    

            if (offset_counter >= info->offset){
                buffer[buffer_pos++] = te->text[text_pos];
                while (length-- > 1) buffer[buffer_pos++] = te->text[++text_pos];
                col++;
            }
            else{
                offset_counter++;
            }
   
            text_pos++;
        }

        while (text_pos < text_len && te->text[text_pos] != '\n') text_pos++;
        if (text_pos < text_len && te->text[text_pos] == '\n') text_pos++;
        
        while (col < info->sizex) {
            buffer[buffer_pos++] = ' ';
            col++;
        }

        
        //buffer_pos += sprintf(buffer + buffer_pos, "%s", " |");
    }



    sprintf(buffer + buffer_pos, "\033[%ld;%ldH\033[?25h", te->cursor_lin+info->posy+1, te->cursor_col+4-info->offset);
    fputs(buffer, stdout);
    // fflush(stdout);
}


void render_buffer(buffer_renderer* info){
    static text_exchange te = {NULL, 0, 0, 0, 0};
    if (te.text == NULL){
        te.text = malloc(10001 * sizeof(uchar));
        te.text_size = 10001;
        //talbvez futuro multiplos simultaneo
    }
    get_textexchange(*(info->gap_buffer), &te);
    if (!te.ok){
        printf("vai se foder");
        return;
    }

    //printf("[%ld %ld]", te.cursor_col, te.cursor_lin);

    render(&te, info);
}