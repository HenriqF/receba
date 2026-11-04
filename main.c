#include "gapbuffer.h"
#include "input/input.h"
#include "hash/hash.h"
#include "render/render.h"

GapBuffer text_area;
buffer_renderer text_area_renderer;

term_size ts;

int handle_acao(ACAOKB a){
    int ret = 1;

    switch (a) {
        case ACAO_direita:
            move_right(&text_area);
            break;

        case ACAO_esquerda:
            move_left(&text_area);
            break;

        case ACAO_backspace:
            delete_char(&text_area);
            break;
        
        case ACAO_aumentar_caixa:
            text_area_renderer.posx ++;
            text_area_renderer.posy ++;
            break;

                    
        case ACAO_diminuir_caixa:
            text_area_renderer.posy > 1 ? text_area_renderer.posy -- : text_area_renderer.posy;
            text_area_renderer.posx > 1 ? text_area_renderer.posx -- : text_area_renderer.posx;
            break;

        case ACAO_aumentar_offset:
            printf("dfasfasdf");
            text_area_renderer.offset ++;
            break;

        case ACAO_diminuir_offset:
            text_area_renderer.offset >= 1 ? text_area_renderer.offset -- : text_area_renderer.offset;
            break;

        default:
            ret = 0;
            break;
    }

    return ret;
}

void main_loop(){
    uchar c = get_input();
    if (c == 27) {
        handle_acao(get_acao_escape());
        goto fim_loop;
    }

    ACAOKB a = get_acao_padrao(c);
    if (a != ACAO_nada){
        handle_acao(a);
        goto fim_loop;
    }
    insert_char(&text_area, c);

    
    fim_loop:
    get_terminal_size(&ts);
    clear_screen();

    render_buffer(&text_area_renderer);
}

void init(){
    OS_init();
    init_gb(&text_area, (size_t)5);
    init_hashacoes();

    text_area_renderer = (buffer_renderer){0, 0, 100, 40, 0, &text_area};
    clear_screen();
}
void final(){
    OS_close();
}

int main(){
    init();

    uchar texto1[] = "texot exemmplo....\n";
    uchar texto2[] = "abcdefghijklmnopqrstuvwxyz\n";
    uchar texto3[] = "g6sadyfpjknç3214sfdaf\n";
    uchar texto4[] = "jaaaaaaaaaaa 547894\n";
    insert_string(&text_area, texto1, 19);
    insert_string(&text_area, texto2, 27);
    insert_string(&text_area, texto3, 23);
    insert_string(&text_area, texto4, 20);

    get_terminal_size(&ts);
    render_buffer(&text_area_renderer);

    while (1){
        main_loop();
    }

    final();
    return 0;
}

