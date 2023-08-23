#ifndef B_TREE_H
#define B_TREE_H

#define MAX_KEYS 10
#define MIN_KEYS ((MAX_KEYS + 1) / 2)

struct BTreeNode {
    int keys[MAX_KEYS];
    struct BTreeNode* children[MAX_KEYS + 1];
    int num_keys;
    int is_leaf;
};

struct BTreeNode* arvB_cria();
struct BTreeNode* arvB_criaNo();
void arvB_destroi(struct BTreeNode* root);
void arvB_splitNo(struct BTreeNode* parent, int index);
void arvB_balanceNo(struct BTreeNode* parent, int index);
void arvB_insere(struct BTreeNode** root, int key);
void arvB_removeChave(struct BTreeNode* node, int index);
void arvB_removeNo(struct BTreeNode** root, int key);
void arvB_imprime(struct BTreeNode* root);
struct BTreeNode* arvB_busca(struct BTreeNode* root, int key);
int arvB_qnt_nos(struct BTreeNode* root);
int arvB_qnt_chaves(struct BTreeNode* root);

#endif