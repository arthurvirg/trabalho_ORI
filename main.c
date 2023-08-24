#include <stdio.h>
#include <stdlib.h>
#include "bEstrela.h"
#include <stdbool.h>

int main() {

    int vetor[50];
    for(int i = 1; i <= 50; i++)
    {
        vetor[i] = rand() %100 ;
    }

    ArvB* minha_arvore = arvB_cria();
    
    for (int j = 1; j <= 50; j++) {
        arvB_insere(minha_arvore, vetor[j]);
    }

    arvB_imprime(minha_arvore);
    printf("\n");

    bool result = arvB_busca(minha_arvore, 30);
    if (result){
        printf("Valor 30 encontrado!\n");
    }
    else{
        printf("Valor 30 nao encontrado!\n");
    }
    
    int qtd_nos1 = arvB_qtd_nos(minha_arvore);
    printf("Qtd de nos: %d\n", qtd_nos1);

    int qtd_chaves1 = arvB_qtd_chaves(minha_arvore);
    printf("Qtd de chaves: %d\n", qtd_chaves1);

    arvB_remove(minha_arvore, 99);

    arvB_imprime(minha_arvore);
    printf("\n");

    int qtd_nos2 = arvB_qtd_nos(minha_arvore);
    printf("Qtd de nos: %d\n", qtd_nos2);

    int qtd_chaves2 = arvB_qtd_chaves(minha_arvore);
    printf("Qtd de chaves: %d\n", qtd_chaves2);

    arvB_destroi(minha_arvore);
   
return 0;
}