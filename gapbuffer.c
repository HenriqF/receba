#include "gapbuffer.h"

int get_char_length(uchar c){
    if ((c & 128) == 0) return 1;
    if ((c & 224) == 192) return 2;
    if ((c & 240) == 224) return 3;
    if ((c & 248) == 240) return 4;
    
    printf("Caractere de tamanho estranho...\n");
    exit(-1);
    return -1;
}

//se for continuacao:  (c & 192) == 128


void init_gb(GapBuffer* gb, size_t gap_size){
    if (gap_size < 1) gap_size = 1;

    gb->buffer = calloc(gap_size, gap_size*sizeof(uchar));
    gb->buffer_size = gap_size;
    gb->gap_size = gap_size;
    gb->gapl = 0;
    gb->gapr = gap_size-1;
}

uchar* get_text(GapBuffer gb){
    uchar* result = malloc(gb.buffer_size*sizeof(uchar)+1);

    size_t result_index = 0;
    for(size_t i = 0; i < gb.gapl; i++){
        if (gb.buffer[i] != 0) result[result_index++] = gb.buffer[i];
    }
    for(size_t i = gb.gapr+1; i < gb.buffer_size; i++){
        if (gb.buffer[i] != 0) result[result_index++] = gb.buffer[i];
    }
    result[result_index] = '\0';

    return result;
}


//grow
void grow(GapBuffer* gb){
    uchar* temp = realloc(gb->buffer, gb->buffer_size+gb->gap_size);
    gb->buffer = temp;
    gb->buffer_size += gb->gap_size;

    for (size_t i = gb->buffer_size-1; i > gb->buffer_size-gb->gap_size; i--){
        gb->buffer[i] = 0;
    }

    if (gb->gapr < gb->buffer_size-gb->gap_size-1){
        size_t afteri = gb->gapl+1;
        size_t l = gb->buffer_size-gb->gap_size-1-gb->gapr;

        memmove(gb->buffer+(gb->buffer_size-l), gb->buffer+afteri, l);  
        memset(gb->buffer+afteri, '\0', gb->gap_size);
    }

    gb->gapr += gb->gap_size;
}


//insert, delete
void insert_string(GapBuffer* gb, uchar* string, size_t len){
    for (size_t i = 0; i < len; i++){
        insert_char(gb, string[i]);
    }
}

void insert_char(GapBuffer* gb, uchar c){
    if (gb->gapl == gb->gapr){
        grow(gb);
    }

    gb->buffer[gb->gapl] = c;
    gb->gapl++;
}

void delete_char(GapBuffer* gb){
    if (gb->gapl <= 0){
        return;
    }


    int fica_loopando = 1;
    do{
        uchar temp = gb->buffer[gb->gapl-1];
        gb->buffer[gb->gapl-1] = 0;
        gb->gapl--;
        if ((temp & 192) != 128) fica_loopando = 0; 
    } while (fica_loopando);


}


//movingfs
void move_left(GapBuffer* gb){
    if (gb->gapl == 0){
        return;
    }

    while (1){
        gb->gapl--;
        uchar temp = gb->buffer[gb->gapl];
        gb->buffer[gb->gapl] = gb->buffer[gb->gapr];
        gb->buffer[gb->gapr] = temp;
        gb->gapr--;
        if ((temp & 192) != 128) break; 
    }

}

void move_right(GapBuffer* gb){
    if (gb->gapr == gb->buffer_size-1){
        return;
    }


    int length = get_char_length(gb->buffer[gb->gapr+1]);

    while(length > 0){
        gb->gapr++;
        uchar temp = gb->buffer[gb->gapr];
        gb->buffer[gb->gapr] = gb->buffer[gb->gapl];
        gb->buffer[gb->gapl] = temp;
        gb->gapl++;

        length--;
    }

   

}