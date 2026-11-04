#include "input.h"
HashMap acaomapping = (HashMap){100, 0, NULL};


ACAOKB get_acao_escape(){
    char cmd[] = {getch(), getch(), 0};
    printf("%s", cmd);
    return get_value(acaomapping, cmd);
    // printf("%s -> %d", cmd, get_value(acaomapping, cmd));
}

ACAOKB get_acao_padrao(uchar c){
    switch (c){
        case 127:
            return ACAO_backspace;
            break;
        
        default:
            break;
    }

    return ACAO_nada;
}

uchar get_input(){
    uchar c = getch();
    printf("%d", c);

    return c;
}


void init_hashacoes(){
    init_hashmap(&acaomapping);

    struct {
        char* codigo;
        ACAOKB acao;
    } m [] = {
        {"[A", ACAO_cima},
        {"[B", ACAO_baixo},
        {"[C", ACAO_direita},
        {"[D", ACAO_esquerda},
        {"[[", ACAO_aumentar_caixa},
        {"]]", ACAO_diminuir_caixa},
        {"//", ACAO_aumentar_offset},
        {";;", ACAO_diminuir_offset}
    };
    size_t len_m = sizeof(m)/sizeof(m[0]);

    for (size_t i =0; i < len_m; i++){
        set_key(&acaomapping, m[i].codigo, m[i].acao);
    }
}