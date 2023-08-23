#include <stdio.h>
#include <stdlib.h>
#include "bEstrela.h"

struct BTreeNode* createTree() {
    struct BTreeNode* root = createNode();
    return root;
}

struct BTreeNode* createNode() {
    struct BTreeNode* newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    newNode->num_keys = 0;
    newNode->is_leaf = 1;
    for (int i = 0; i <= MAX_KEYS; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

void destroyTree(struct BTreeNode* root) {
    if (root != NULL) {
        for (int i = 0; i <= root->num_keys; i++) {
            destroyTree(root->children[i]);
        }
        free(root);
    }
}

void mergeNodes(struct BTreeNode* parent, int index) {
    struct BTreeNode* leftChild = parent->children[index];
    struct BTreeNode* rightChild = parent->children[index + 1];
    
    leftChild->keys[leftChild->num_keys] = parent->keys[index];
    
    for (int i = 0; i < rightChild->num_keys; i++) {
        leftChild->keys[leftChild->num_keys + 1 + i] = rightChild->keys[i];
    }
    
    if (!rightChild->is_leaf) {
        for (int i = 0; i <= rightChild->num_keys; i++) {
            leftChild->children[leftChild->num_keys + 1 + i] = rightChild->children[i];
        }
    }
    
    for (int i = index; i < parent->num_keys - 1; i++) {
        parent->keys[i] = parent->keys[i + 1];
        parent->children[i + 1] = parent->children[i + 2];
    }
    
    leftChild->num_keys += rightChild->num_keys + 1;
    parent->num_keys--;
    
    free(rightChild);
}

void removeKey(struct BTreeNode* node, int index) {
    for (int i = index; i < node->num_keys - 1; i++) {
        node->keys[i] = node->keys[i + 1];
    }
    node->num_keys--;
    printf("Chave %d removida com sucesso!", index);
}

void splitNode(struct BTreeNode* parent, int index) {
    struct BTreeNode* newNode = createNode();
    struct BTreeNode* oldNode = parent->children[index];
    newNode->is_leaf = oldNode->is_leaf;
    newNode->num_keys = MAX_KEYS / 2;

    for (int i = 0; i < MAX_KEYS / 2; i++) {
        newNode->keys[i] = oldNode->keys[i + MAX_KEYS / 2];
    }

    if (!oldNode->is_leaf) {
        for (int i = 0; i <= MAX_KEYS / 2; i++) {
            newNode->children[i] = oldNode->children[i + MAX_KEYS / 2];
            oldNode->children[i + MAX_KEYS / 2] = NULL;
        }
    }

    oldNode->num_keys = MAX_KEYS / 2;
    
    for (int i = parent->num_keys; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
    }
    
    parent->children[index + 1] = newNode;
    
    for (int i = parent->num_keys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }
    
    parent->keys[index] = oldNode->keys[MAX_KEYS / 2];
    parent->num_keys++;
}

void balanceNode(struct BTreeNode* parent, int index){
    if (parent == NULL) {
        return;
    }

    struct BTreeNode* child = parent->children[index];

    if (child->num_keys > MAX_KEYS) {
        splitNode(parent, index);
    } else if (child->num_keys < MIN_KEYS) {
        int leftIndex = index - 1;
        int rightIndex = index + 1;

        if (leftIndex >= 0 && parent->children[leftIndex]->num_keys > MIN_KEYS) {
            // Move uma chave do nó pai para o filho carente
            child->num_keys++;
            for (int i = child->num_keys - 1; i > 0; i--) {
                child->keys[i] = child->keys[i - 1];
            }
            child->keys[0] = parent->keys[leftIndex];
            parent->keys[leftIndex] = parent->children[leftIndex]->keys[parent->children[leftIndex]->num_keys - 1];
            parent->children[leftIndex]->num_keys--;
        } else if (rightIndex <= parent->num_keys && parent->children[rightIndex]->num_keys > MIN_KEYS) {
            // Move uma chave do nó pai para o filho carente
            child->num_keys++;
            child->keys[child->num_keys - 1] = parent->keys[index];
            parent->keys[index] = parent->children[rightIndex]->keys[0];
            for (int i = 0; i < parent->children[rightIndex]->num_keys - 1; i++) {
                parent->children[rightIndex]->keys[i] = parent->children[rightIndex]->keys[i + 1];
            }
            parent->children[rightIndex]->num_keys--;
        } else if (leftIndex >= 0) {
            // Fusão com o filho à esquerda
            mergeNodes(parent, leftIndex);
        } else {
            // Fusão com o filho à direita
            mergeNodes(parent, index);
        }
    }
}

void removeNode(struct BTreeNode** root, int key) {
    if (*root == NULL) {
        return;
    }

    struct BTreeNode* currentNode = *root;
    struct BTreeNode* parent = NULL;
    int index;

    while (!currentNode->is_leaf) {
        parent = currentNode;
        for (index = 0; index < currentNode->num_keys; index++) {
            if (key < currentNode->keys[index]) {
                break;
            }
        }
        currentNode = currentNode->children[index];
    }

    for (index = 0; index < currentNode->num_keys; index++) {
        if (key == currentNode->keys[index]) {
            break;
        }
    }

    if (index < currentNode->num_keys && currentNode->keys[index] == key) {
        if (currentNode->is_leaf) {
            removeKey(currentNode, index);
        } else {
            // Substitua o nó a ser removido pelo maior valor do nó à esquerda ou pelo menor valor do nó à direita.
            struct BTreeNode* pred = currentNode->children[index];
            while (!pred->is_leaf) {
                pred = pred->children[pred->num_keys];
            }
            currentNode->keys[index] = pred->keys[pred->num_keys - 1];
            removeNode(&(currentNode->children[index]), pred->keys[pred->num_keys - 1]);
        }
    } else {
        if (!currentNode->is_leaf) {
            removeNode(&(currentNode->children[index]), key);
        }
    }
    
    // Balanceamento após a remoção
    balanceNode(parent, index);

    // Se a &raiz ficou vazia, atualize-a
    if (parent == NULL && (*root)->num_keys == 0) {
        struct BTreeNode* newRoot = (*root)->children[0];
        free(*root);
        *root = newRoot;
    }
    printf("No %d removido com sucesso!", key);
}

void insert(struct BTreeNode** root, int key) {
    if (*root == NULL) {
        struct BTreeNode* newNode = createNode();
        newNode->keys[0] = key;
        newNode->num_keys = 1;
        *root = newNode;
        return;
    }

    struct BTreeNode* currentNode = *root;
    struct BTreeNode* parent = NULL;
    int index;

    while (!currentNode->is_leaf) {
        parent = currentNode;
        for (index = 0; index < currentNode->num_keys; index++) {
            if (key < currentNode->keys[index]) {
                break;
            }
        }
        currentNode = currentNode->children[index];
    }

    for (index = 0; index < currentNode->num_keys; index++) {
        if (key < currentNode->keys[index]) {
            break;
        }
    }

    if (currentNode->num_keys < MAX_KEYS) {
        for (int i = currentNode->num_keys; i > index; i--) {
            currentNode->keys[i] = currentNode->keys[i - 1];
        }
        currentNode->keys[index] = key;
        currentNode->num_keys++;
    } else {
        splitNode(parent, index);
        if (key >= parent->keys[index]) {
            index++;
        }
        insert(&(parent->children[index]), key);
    }
    
    balanceNode(parent, index);
}

void inorderTraversal(struct BTreeNode* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->num_keys; i++) {
            inorderTraversal(root->children[i]);
            printf("%d ", root->keys[i]);
        }
        inorderTraversal(root->children[i]);
    }
}

struct BTreeNode* search(struct BTreeNode* root, int key) {
    if (root == NULL) {
        return NULL;
    }

    int index = 0;
    while (index < root->num_keys && key > root->keys[index]) {
        index++;
    }

    if (index < root->num_keys && key == root->keys[index]) {
        return root;
    }

    if (root->is_leaf) {
        return NULL;
    }

    return search(root->children[index], key);
}

int countNodes(struct BTreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    int count = 1;
    for (int i = 0; i <= root->num_keys; i++) {
        count += countNodes(root->children[i]);
    }
    printf("%d ", count);
    return 0;
}

int countKeys(struct BTreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    int count = root->num_keys;
    for (int i = 0; i <= root->num_keys; i++) {
        count += countKeys(root->children[i]);
    }
    printf("%d ", count);
    return 0;
}

void printTree(struct BTreeNode* root) {
    if (root != NULL) {
        int i;
        for (i = 0; i < root->num_keys; i++) {
            printTree(root->children[i]);
            printf("%d ", root->keys[i]);
        }
        printTree(root->children[i]);
    }
}



