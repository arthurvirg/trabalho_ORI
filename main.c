#include <stdio.h>
#include <stdlib.h>
#include "bEstrela.h"
#include <stdbool.h>

int main() {

    ArvB minha_arvore = arvB_cria();
   
    arvB_insere(&minha_arvore, 0);
    arvB_insere(&minha_arvore, 1);
    arvB_insere(&minha_arvore, 2);
    arvB_insere(&minha_arvore, 5);
    arvB_insere(&minha_arvore, 6);
    arvB_insere(&minha_arvore, 7);
    arvB_insere(&minha_arvore, 8);
    arvB_insere(&minha_arvore, 9);
    arvB_insere(&minha_arvore, 10);
    arvB_insere(&minha_arvore, 12);
    arvB_insere(&minha_arvore, 16);
    arvB_insere(&minha_arvore, 18);   
    arvB_insere(&minha_arvore, 25);
    arvB_insere(&minha_arvore, 27);
    arvB_insere(&minha_arvore, 28);
    arvB_insere(&minha_arvore, 29);
    arvB_insere(&minha_arvore, 30);

    arvB_imprime_pais_nivel(minha_arvore);
    arvB_imprime_folhas_nivel(minha_arvore);
    printf("\n");

    arvB_busca(minha_arvore, 30);
    
    
    int qtd_nos1 = arvB_qtd_nos(minha_arvore);
    printf("Qtd de nos: %d\n", qtd_nos1);

    int qtd_chaves1 = arvB_qtd_chaves(minha_arvore);
    printf("Qtd de chaves: %d\n\n", qtd_chaves1);

    arvB_remove(&minha_arvore, 8);
    printf("\n");

    arvB_imprime_pais_nivel(minha_arvore);
    arvB_imprime_folhas_nivel(minha_arvore);
    printf("\n");

    int qtd_nos2 = arvB_qtd_nos(minha_arvore);
    printf("Qtd de nos: %d\n", qtd_nos2);

    int qtd_chaves2 = arvB_qtd_chaves(minha_arvore);
    printf("Qtd de chaves: %d\n", qtd_chaves2);

    arvB_destroi(&minha_arvore);
   
return 0;
}