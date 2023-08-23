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

struct BTreeNode* createTree();
struct BTreeNode* createNode();
void splitNode(struct BTreeNode* parent, int index);
void balanceNode(struct BTreeNode* parent, int index);
void insert(struct BTreeNode** root, int key);
void removeKey(struct BTreeNode* node, int index);
void removeNode(struct BTreeNode** root, int key);
struct BTreeNode* search(struct BTreeNode* root, int key);
int countNodes(struct BTreeNode* root);
int countKeys(struct BTreeNode* root);
void destroyTree(struct BTreeNode* root);
void inorderTraversal(struct BTreeNode* root);
void printTree(struct BTreeNode* root);

#endif