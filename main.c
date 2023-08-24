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
        printf("Chave encontrada!\n");
    }
    else{
        printf("Chave nao encontrada!\n");
    }

    //arvB_remove(minha_arvore, 50);

    arvB_imprime(minha_arvore);
    printf("\n");

    int qtd_nos = arvB_qtd_nos(minha_arvore);
    printf("%d\n", qtd_nos);

    int qtd_chaves = arvB_qtd_chaves(minha_arvore);
    printf("%d\n", qtd_chaves);

    arvB_destroi(minha_arvore);

    //arvB_imprime(minha_arvore);
    printf("\n");
   
return 0;
}