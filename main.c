#include <stdio.h>
#include <stdlib.h>
#include "bEstrela.h"
#include <stdbool.h>

int main() {
    struct BTreeNode* root = arvB_cria();
        int keys[] = {50, 20, 70, 10, 30, 5, 15, 25, 60, 80};
            int num_keys = sizeof(keys) / sizeof(keys[0]);

            for (int i = 0; i < num_keys; i++) {
                arvB_insere(&root, keys[i]);
            }
    
    arvB_imprime(root);
    printf("\n");

    arvB_removeChave(root, 3);
    printf("\n");

    arvB_imprime(root);
    printf("\n");

    arvB_removeNo(&root, 80);
    printf("\n");

    arvB_imprime(root);
    printf("\n");

    arvB_qnt_nos(root);
    printf("\n");

    arvB_qnt_chaves(root);
    printf("\n");

    bool result = arvB_busca(root, 30);
    if (result){
        printf("Chave encontrada!");
    }
    else{
        printf("Chave não encontrada!");
    }

return 0;
}