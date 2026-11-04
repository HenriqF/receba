#ifndef INPUT
#define INPUT

#include "../OS/lin.h"
#include "../hash/hash.h"
#define uchar unsigned char

typedef enum {
    ACAO_nada,
    ACAO_cima,
    ACAO_baixo,
    ACAO_direita,
    ACAO_esquerda,
    ACAO_backspace,

    ACAO_aumentar_caixa,
    ACAO_diminuir_caixa,
    ACAO_aumentar_offset,
    ACAO_diminuir_offset,
} ACAOKB;


uchar get_input();
ACAOKB get_acao_escape();
ACAOKB get_acao_padrao(uchar c);

void init_hashacoes();

#endif