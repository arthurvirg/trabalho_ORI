#ifndef B_TREE_H
#define B_TREE_H

#define MAX_CHAVES 6    
#define MIN_CHAVES ((2 * MAX_CHAVES - 1) / 3)

typedef struct NO {
    int chaves[MAX_CHAVES - 1];
    struct NO* filho[MAX_CHAVES];
    int num_chaves;
    int folha;
}NoArvB;

typedef NoArvB* ArvB;

ArvB* arvB_cria();
NoArvB* arvB_cria_no();
void arvB_destroiNO(NoArvB* no);
void arvB_destroi(ArvB* raiz);
void arvB_mergeNo(NoArvB* no_pai, int posicao);
void arvB_splitNo(NoArvB* no_pai, int posicao);
void arvB_balanceNo(NoArvB* no_pai, int posicao);
int arvB_insere_nao_cheio(NoArvB* no, int valor);
int arvB_insere(ArvB* raiz, int valor);
void arvB_removeChave(NoArvB* no, int posicao);
void arvB_remove(ArvB* raiz, int chave);
void arvB_imprime_recursivo(NoArvB* no);
void arvB_imprime(ArvB* raiz);
int arvB_busca_chave(NoArvB* no, int chave);
int arvB_busca(ArvB* raiz, int valor);
int arvB_qtd_nos(ArvB* raiz);
int arvB_qtd_nos_recursivo(NoArvB* no);
int arvB_qtd_chaves(ArvB* raiz);
int arvB_qtd_chaves_recursivo(NoArvB* no);

#endif