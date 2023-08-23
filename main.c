#include <stdio.h>
#include <stdlib.h>
#include "bEstrela.h"
#include <stdbool.h>

int main() {
    struct BTreeNode* root = createTree();
        int keys[] = {50, 20, 70, 10, 30, 5, 15, 25, 60, 80};
            int num_keys = sizeof(keys) / sizeof(keys[0]);

            for (int i = 0; i < num_keys; i++) {
                insert(&root, keys[i]);
            }
    
    inorderTraversal(root);
    printf("\n");

    removeKey(root, 3);
    printf("\n");

    inorderTraversal(root);
    printf("\n");

    removeNode(&root, 80);
    printf("\n");

    inorderTraversal(root);
    printf("\n");

    countNodes(root);
    printf("\n");

    countKeys(root);
    printf("\n");

    bool result = search(root, 30);
    if (result){
        printf("Chave encontrada!");
    }
    else{
        printf("Chave não encontrada!");
    }

return 0;
}