#include <stdio.h>
#include <stdlib.h>
#include "bEstrela.h"


ArvB* arvB_cria() {
    ArvB* novaArvore = (ArvB*)malloc(sizeof(ArvB));
    if (novaArvore != NULL) {
        NoArvB* raiz = arvB_cria_no();
        if (raiz != NULL) {
            raiz->num_chaves = 1;
            raiz->folha = 1;
            *novaArvore = raiz;
        } else {
            free(novaArvore);
            novaArvore = NULL;
        }
    }
    return novaArvore;
}

NoArvB* arvB_cria_no() {
    NoArvB* no = (NoArvB*)malloc(sizeof(NoArvB));
    if (no != NULL) {
        no->num_chaves = 0;
        no->folha = 1;
        for (int i = 0; i < MAX_CHAVES; i++) {
            no->filho[i] = NULL;
        }
        no->filho[MAX_CHAVES] = NULL; // Último ponteiro para filho
    }
    return no;
}

void arvB_destroiNO(NoArvB* no) {
    if (no != NULL) {
        for (int i = 0; i <= no->num_chaves; i++) {
            arvB_destroiNO(no->filho[i]);
        }
        free(no);
    } 
}

void arvB_destroi(ArvB* raiz){
    if(raiz == NULL || *raiz == NULL){
        return;
    }
    arvB_destroiNO(*raiz);
    free(raiz);
}

void arvB_mergeNo(NoArvB* no_pai, int posicao) {
    NoArvB* filhoEsq = no_pai->filho[posicao];
    NoArvB* filhoDir = no_pai->filho[posicao + 1];
    
    filhoEsq->chaves[filhoEsq->num_chaves] = no_pai->chaves[posicao];
    
    for (int i = 0; i < filhoDir->num_chaves; i++) {
        filhoEsq->chaves[filhoEsq->num_chaves + 1 + i] = filhoDir->chaves[i];
    }
    
    if (!filhoDir->folha) {
        for (int i = 0; i <= filhoDir->num_chaves; i++) {
            filhoEsq->filho[filhoEsq->num_chaves + 1 + i] = filhoDir->filho[i];
        }
    }
    
    for (int i = posicao; i < no_pai->num_chaves - 1; i++) {
        no_pai->chaves[i] = no_pai->chaves[i + 1];
        no_pai->filho[i + 1] = no_pai->filho[i + 2];
    }
    
    filhoEsq->num_chaves += filhoDir->num_chaves + 1;
    no_pai->num_chaves--;
    
    free(filhoDir);
}

void arvB_splitNo(ArvB no_pai, int posicao) {
    ArvB filho = no_pai->filho[posicao];
    ArvB* novo_filho = arvB_cria();
    (*novo_filho)->folha = filho->folha;
    (*novo_filho)->num_chaves = MAX_CHAVES / 2 - 1;

    for (int i = 0; i < MAX_CHAVES / 2 - 1; i++)
    {
        (*novo_filho)->chaves[i] = filho->chaves[i + MAX_CHAVES / 2];
    }

    if (!filho->folha)
    {
        for (int i = 0; i < MAX_CHAVES / 2; i++)
        {
            (*novo_filho)->filho[i] = filho->filho[i + MAX_CHAVES / 2];
        }
    }

    filho->num_chaves = MAX_CHAVES / 2 - 1;

    for (int i = no_pai->num_chaves; i >= posicao + 1; i--)
    {
        no_pai->filho[i + 1] = no_pai->filho[i];
    }

    no_pai->filho[posicao + 1] = (*novo_filho);

    for (int i = no_pai->num_chaves - 1; i >= posicao; i--)
    {
        no_pai->chaves[i + 1] = no_pai->chaves[i];
    }

    no_pai->chaves[posicao] = filho->chaves[MAX_CHAVES / 2 - 1];
    no_pai->num_chaves++;
}

void arvB_balanceNo(NoArvB* no_pai, int posicao){
     if (no_pai == NULL) {
        return;
    }

    NoArvB* filho = no_pai->filho[posicao];

    if (filho->num_chaves > MAX_CHAVES) {
        arvB_splitNo(no_pai, posicao);
    } else if (filho->num_chaves < MIN_CHAVES) {
        int esquerda = posicao - 1;
        int direita = posicao + 1;

        if (esquerda >= 0 && no_pai->filho[esquerda]->num_chaves > MIN_CHAVES) {
            // Move uma chave do nó pai para o filho carente
            NoArvB* filhoEsq = no_pai->filho[esquerda];
            filho->chaves[filho->num_chaves] = no_pai->chaves[esquerda];
            filho->num_chaves++;
            no_pai->chaves[esquerda] = filhoEsq->chaves[filhoEsq->num_chaves - 1];
            filhoEsq->num_chaves--;

            if (!filho->folha) {
                filho->filho[filho->num_chaves] = filhoEsq->filho[filhoEsq->num_chaves + 1];
                filhoEsq->filho[filhoEsq->num_chaves + 1] = NULL;
            }
        } else if (direita <= no_pai->num_chaves && no_pai->filho[direita]->num_chaves > MIN_CHAVES) {
            // Move uma chave do nó pai para o filho carente
            NoArvB* filhoDir = no_pai->filho[direita];
            filho->num_chaves++;
            for (int i = filho->num_chaves - 1; i > 0; i--) {
                filho->chaves[i] = filho->chaves[i - 1];
            }
            filho->chaves[0] = no_pai->chaves[posicao];
            no_pai->chaves[posicao] = filhoDir->chaves[0];
            for (int i = 0; i < filhoDir->num_chaves - 1; i++) {
                filhoDir->chaves[i] = filhoDir->chaves[i + 1];
            }
            filho->num_chaves++;
            filhoDir->num_chaves--;

            if (!filho->folha) {
                filho->filho[0] = filhoDir->filho[0];
                for (int i = 0; i < filhoDir->num_chaves; i++) {
                    filhoDir->filho[i] = filhoDir->filho[i + 1];
                }
            }
        } else if (esquerda >= 0) {
            // Fusão com o filho à esquerda
            arvB_mergeNo(no_pai, esquerda);
        } else {
            // Fusão com o filho à direita
            arvB_mergeNo(no_pai, posicao);
        }
    }
}

int arvB_insere_nao_cheio(NoArvB* no, int valor)
{
    int i = no->num_chaves - 1;

    if (no->folha)
    {
        while (i >= 0 && valor < no->chaves[i])
        {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = valor;
        no->num_chaves++;
    }
    else
    {
        while (i >= 0 && valor < no->chaves[i])
        {
            i--;
        }
        i++;
        if (no->filho[i]->num_chaves == MAX_CHAVES - 1)
        {
            arvB_splitNo(no, i);
            if (valor > no->chaves[i])
            {
                i++;
            }
        }
        arvB_insere_nao_cheio(no->filho[i], valor); 
    }
   
    return 1;
}

int arvB_insere(ArvB* raiz, int valor) {
     ArvB raiz_atual = *raiz;
    if (raiz_atual->num_chaves == MAX_CHAVES - 1)
    {
        ArvB* nova_raiz = arvB_cria();
        (*nova_raiz)->folha = 0;
        (*nova_raiz)->filho[0] = raiz_atual;
        arvB_splitNo((*nova_raiz), 0);
        arvB_insere_nao_cheio((*nova_raiz), valor);
        *raiz = (*nova_raiz);
    }
    else
    {
        arvB_insere_nao_cheio(raiz_atual, valor);
    }
    return 1;
}

void arvB_removeChave(NoArvB* no, int posicao) {
    for (int i = posicao; i < no->num_chaves - 1; i++) {
        no->chaves[i] = no->chaves[i + 1];
    }
    no->num_chaves--;
    printf("No %d removido com sucesso!\n", no->chaves);
}

void arvB_remove(ArvB* raiz, int chave) {
    if (*raiz == NULL) {
        return;
    }

    NoArvB* no_atual = *raiz;
    NoArvB* no_pai = NULL;
    int posicao;

    while (!no_atual->folha) {
        no_pai = no_atual;
        for (posicao = 0; posicao < no_atual->num_chaves; posicao++) {
            if (chave < no_atual->chaves[posicao]) {
                break;
            }
        }
        no_atual = no_atual->filho[posicao];
    }

    for (posicao = 0; posicao < no_atual->num_chaves; posicao++) {
        if (chave == no_atual->chaves[posicao]) {
            break;
        }
    }

    if (posicao < no_atual->num_chaves && no_atual->chaves[posicao] == chave) {
        if (no_atual->folha) {
            arvB_removeChave(no_atual, posicao);
        } else {
            // Substitua o nó a ser removido pelo maior valor do nó à esquerda ou pelo menor valor do nó à direita.
            NoArvB* pred = no_atual->filho[posicao];
            while (!pred->folha) {
                pred = pred->filho[pred->num_chaves];
            }
            no_atual->chaves[posicao] = pred->chaves[pred->num_chaves - 1];
            arvB_remove(&(no_atual->filho[posicao]), pred->chaves[pred->num_chaves - 1]);
        }
    } else {
        if (!no_atual->folha) {
            arvB_remove(&(no_atual->filho[posicao]), chave);
        }
    }
    
    // Balanceamento após a remoção
    arvB_balanceNo(no_pai, posicao);

    // Se a &raiz ficou vazia, atualize-a
    if (no_pai == NULL && (*raiz)->num_chaves == 0) {
        NoArvB* newraiz = (*raiz)->filho[0];
        free(*raiz);
        *raiz = newraiz;
    }
}

void arvB_imprime_recursivo(NoArvB* no) {
    if (no != NULL) {
        for (int i = 0; i < no->num_chaves; i++) {
            printf("%d ", no->chaves[i]);
        }

        for (int i = 0; i <= no->num_chaves; i++) {
            arvB_imprime_recursivo(no->filho[i]);
        }
    }
}

void arvB_imprime(ArvB* raiz) {
    if (raiz != NULL && *raiz != NULL) {
        arvB_imprime_recursivo(*raiz);
    }
}

int arvB_busca_chave(NoArvB* no, int chave) {
    if (no == NULL) {
        return 0;
    }

    int posicao = 0;
    while (posicao < no->num_chaves && chave > no->chaves[posicao]) {
        posicao++;
    }

    if (posicao < no->num_chaves && chave == no->chaves[posicao]) {
        return 1;
    }

    if (no->folha) {
        return 0;
    }

    return arvB_busca_chave(no->filho[posicao], chave);
}

int arvB_busca(ArvB* raiz, int valor) {
    if (raiz == NULL || *raiz == NULL) {
        return 0;
    }
    return arvB_busca_chave(*raiz, valor);
}

int arvB_qtd_nos_recursivo(NoArvB* no) {
    if (no == NULL) {
        return 0;
    }

    int cont = 1;
    if (!no->folha){
        for (int i = 0; i <= no->num_chaves; i++) {
            cont += arvB_qtd_nos_recursivo(no->filho[i]);           
        }
    }
    return cont;
}

int arvB_qtd_nos(ArvB* raiz) {
    if (raiz == NULL || *raiz == NULL) {
        return 0;
    }
    
    return arvB_qtd_nos_recursivo(*raiz);
}

int arvB_qtd_chaves_recursivo(NoArvB* no) {
    if (no == NULL) {
        return 0;
    }

    int cont = no->num_chaves; 
    if(!no->folha){
        for (int i = 0; i <= no->num_chaves; i++) {
            cont = cont + arvB_qtd_chaves_recursivo(no->filho[i]);     
        }
    }
    return cont;
}

int arvB_qtd_chaves(ArvB* raiz) {
    if (raiz == NULL || *raiz == NULL) {
        return 0;
    }
    
    return arvB_qtd_chaves_recursivo(*raiz);
}