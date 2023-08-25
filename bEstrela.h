#ifndef B_TREE_H
#define B_TREE_H

#define ordem 8    

typedef struct NO {
    int chaves[ordem - 1];
    struct NO* filho[ordem];
    int num_chaves;
    int folha;
}NoArvB;

typedef NoArvB* ArvB;

ArvB arvB_cria();

void arvB_destroiNO(ArvB no);
void arvB_destroi(ArvB* raiz);
void arvB_mergeNo(ArvB no_pai, int posicao);
void arvB_splitNo(ArvB no_pai, int posicao);
void arvB_redistribuir_esquerda(ArvB no_pai, int posicao);
void arvB_redistribuir_direita(ArvB no_pai, int posicao);
void arvB_balanceNo(ArvB no_atual, int posicao);
int arvB_insere_nao_cheio(ArvB no, int valor);
int arvB_insere(ArvB* raiz, int valor);
void arvB_removeChave(ArvB no, int posicao);
void arvB_remove(ArvB* raiz, int chave);
void arvB_imprime_pais(NoArvB* no, int nivel, int posicao);
void arvB_imprime_pais_nivel(ArvB raiz);
void arvB_imprime_folhas(NoArvB* no, int nivel, int posicao);
void arvB_imprime_folhas_nivel(ArvB raiz);
int arvB_busca_chave(ArvB no, int chave);
int arvB_busca(ArvB raiz, int valor);
int arvB_qtd_nos_recursivo(ArvB no);
int arvB_qtd_nos(ArvB raiz);
int arvB_qtd_chaves_recursivo(ArvB no);
int arvB_qtd_chaves(ArvB raiz);
#endif