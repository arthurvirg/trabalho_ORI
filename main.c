#include <stdio.h>
#include <stdlib.h>
#include "bEstrela.h"
#include <stdbool.h>

int main() {
    ArvB* root = arvB_cria();
        int keys[] = {50, 20, 10, 30, 5, 15, 25, 60, 70, 80, 90, 95, 100, 200};
            int num_keys = sizeof(keys) / sizeof(keys[0]);

            for (int i = 0; i < num_keys; i++) {
                arvB_insere(root, keys[i]);
            }

    arvB_imprime(root);
    printf("\n");

    bool result = arvB_busca(root, 30);
    if (result){
        printf("Chave encontrada!\n");
    }
    else{
        printf("Chave não encontrada!\n");
    }

    arvB_remove(root, 50);

    arvB_imprime(root);
    printf("\n");

    int qtd_nos = arvB_qtd_nos(root);
    printf("%d\n", qtd_nos);

    int qtd_chaves = arvB_qtd_chaves(root);
    printf("%d\n", qtd_chaves);

    arvB_destroi(root);

    //arvB_imprime(root);
    printf("\n");
   
return 0;
}