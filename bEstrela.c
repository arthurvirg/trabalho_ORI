#include <stdio.h>
#include <stdlib.h>
#include "bEstrela.h"


ArvB arvB_cria() {
    ArvB nova_arvore = (ArvB)malloc(sizeof(NoArvB));
    nova_arvore->num_chaves = 0;
    nova_arvore->folha = 1;
    for (int i = 0; i < ordem; i++)
    {
        nova_arvore->filho[i] = NULL;
    }
    return nova_arvore;
}

void arvB_destroiNO(ArvB no) {
    if (no != NULL) {
        if (!no->folha){
            for (int i = 0; i <= no->num_chaves; i++) {
                arvB_destroiNO(no->filho[i]);
            }
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

void arvB_mergeNo(ArvB no_pai, int posicao) {
    ArvB filhoEsq = no_pai->filho[posicao];
    ArvB filhoDir = no_pai->filho[posicao + 1];
    
    int min_chaves = (ordem / 2) - 1;  // Mínimo de chaves permitido

    filhoEsq->chaves[(ordem / 2) - 1] = no_pai->chaves[posicao];
    
    for (int i = 0; i < filhoDir->num_chaves; i++) {
        filhoEsq->chaves[i + (ordem / 2)] = filhoDir->chaves[i];
    }
    
    if (!filhoDir->folha) {
        for (int i = 0; i <= filhoDir->num_chaves; i++) {
            filhoEsq->filho[i + (ordem / 2)] = filhoDir->filho[i];
        }
    }
    
     for (int i = posicao + 1; i < no_pai->num_chaves; i++)
    {
        no_pai->chaves[i - 1] = no_pai->chaves[i];
    }

    for (int i = posicao + 2; i <= no_pai->num_chaves; i++)
    {
        no_pai->filho[i - 1] = no_pai->filho[i];
    }
    
    filhoEsq->num_chaves += filhoDir->num_chaves + 1;
    no_pai->num_chaves--;
    
    free(filhoDir);
    
    if (filhoEsq->num_chaves < min_chaves) {
        // Se o filho esquerdo ficar com menos chaves do que o mínimo permitido, ajuste o balanceamento
        arvB_balanceNo(no_pai, posicao);
    }
}

void arvB_splitNo(ArvB no_pai, int posicao) {
    ArvB filho = no_pai->filho[posicao];
    ArvB novo_filho = arvB_cria();

    int num_chaves_move = (ordem / 2) - 1;  // Número de chaves a serem movidas

    novo_filho = arvB_cria();
    novo_filho->folha = filho->folha;
    novo_filho->num_chaves = num_chaves_move;

    for (int i = 0; i < num_chaves_move; i++) {
        novo_filho->chaves[i] = filho->chaves[i + ordem / 2];
    }

    if (!filho->folha) {
        for (int i = 0; i <= num_chaves_move; i++) {
            novo_filho->filho[i] = filho->filho[i + ordem / 2];
        }
    }

    filho->num_chaves = num_chaves_move;

    for (int i = no_pai->num_chaves; i >= posicao + 1; i--) {
        no_pai->filho[i + 1] = no_pai->filho[i];
    }

    no_pai->filho[posicao + 1] = novo_filho;

    for (int i = no_pai->num_chaves - 1; i >= posicao; i--) {
        no_pai->chaves[i + 1] = no_pai->chaves[i];
    }

    no_pai->chaves[posicao] = filho->chaves[num_chaves_move];
    no_pai->num_chaves++;
}

void arvB_redistribuir_esquerda(ArvB no_pai, int posicao) {
    ArvB filho_esquerda = no_pai->filho[posicao - 1];
    ArvB no_filho = no_pai->filho[posicao];
    
    // Mover a chave do pai para o filho à direita
    no_filho->chaves[0] = no_pai->chaves[posicao - 1];
    no_filho->num_chaves++;

    // Mover a maior chave do filho à esquerda para o pai
    no_pai->chaves[posicao - 1] = filho_esquerda->chaves[filho_esquerda->num_chaves - 1];
    
    // Atualizar os filhos se necessário
    if (!no_filho->folha) {
        no_filho->filho[1] = no_filho->filho[0];
        no_filho->filho[0] = filho_esquerda->filho[filho_esquerda->num_chaves];
    }

    // Atualizar o número de chaves no filho à esquerda
    filho_esquerda->num_chaves--;
}

void arvB_redistribuir_direita(ArvB no_pai, int posicao) {
    ArvB filho_direita = no_pai->filho[posicao + 1];
    ArvB no_filho = no_pai->filho[posicao];

    // Mover a chave do pai para o filho à esquerda
    no_filho->chaves[no_filho->num_chaves] = no_pai->chaves[posicao];
    no_filho->num_chaves++;

    // Mover a menor chave do filho à direita para o pai
    no_pai->chaves[posicao] = filho_direita->chaves[0];

    // Atualizar os filhos se necessário
    if (!no_filho->folha) {
        no_filho->filho[no_filho->num_chaves] = filho_direita->filho[0];
    }

    // Atualizar o número de chaves no filho à direita
    filho_direita->num_chaves--;

    // Deslocar as chaves no filho à direita para a esquerda
    for (int i = 0; i < filho_direita->num_chaves; i++) {
        filho_direita->chaves[i] = filho_direita->chaves[i + 1];
    }

    // Atualizar os filhos se necessário
    if (!filho_direita->folha) {
        for (int i = 0; i <= filho_direita->num_chaves; i++) {
            filho_direita->filho[i] = filho_direita->filho[i + 1];
        }
    }
}

void arvB_balanceNo(ArvB no_pai, int posicao) {
     if (no_pai == NULL) {
        return;
    }

    int min_chaves = (ordem / 2) - 1;  // Mínimo de chaves permitido
    
    // Verificar os irmãos à esquerda e à direita
    int esquerda = posicao - 1;
    int direita = posicao + 1;
    NoArvB* filho_esquerda = (esquerda >= 0) ? no_pai->filho[esquerda] : NULL;
    NoArvB* filho_direita = (direita < no_pai->num_chaves) ? no_pai->filho[direita] : NULL;

    if (filho_esquerda && filho_esquerda->num_chaves > min_chaves) { 
        // Redistribui chaves do filho à esquerda
        arvB_redistribuir_esquerda(no_pai, posicao);

    } else if (filho_direita && filho_direita->num_chaves > min_chaves) {        
        // Redistribui chaves do filho à direita
        arvB_redistribuir_direita(no_pai, posicao);

    } else if (filho_esquerda) {
        // Fusão com o filho à esquerda
        arvB_mergeNo(no_pai, esquerda);
    } else {
        // Fusão com o filho à direita
        arvB_mergeNo(no_pai, posicao);
    }
}

int arvB_insere_nao_cheio(ArvB no, int valor)
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
        if (no->filho[i]->num_chaves == ordem - 1)
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
    if (raiz_atual->num_chaves == ordem - 1)
    {
        ArvB nova_raiz = arvB_cria();
        nova_raiz->folha = 0;
        nova_raiz->filho[0] = raiz_atual;
        arvB_splitNo(nova_raiz, 0);
        arvB_insere_nao_cheio(nova_raiz, valor);
        *raiz = nova_raiz;
    }
    else
    {
        arvB_insere_nao_cheio(raiz_atual, valor);
    }
    return 1;
}

void arvB_removeChave(ArvB no, int posicao) {
    for (int i = posicao; i < no->num_chaves - 1; i++) {
        no->chaves[i] = no->chaves[i + 1];
    }
    no->num_chaves--;
}

void  arvB_remove(ArvB* raiz, int chave) {
    if (*raiz == NULL) {
        return;
    }
    
    NoArvB* no_atual = *raiz;
    NoArvB* no_pai = NULL;
    int posicao = 0; 

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
            printf("Chave %d removida com sucesso!\n", chave);
            arvB_removeChave(no_atual, posicao);
        } else {
            // Substitui o nó a ser removido pelo maior valor do nó à esquerda ou pelo menor valor do nó à direita.
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

    if (no_pai == NULL && (*raiz)->num_chaves == 0) {
        NoArvB* nova_raiz = (*raiz)->filho[0];
        free(*raiz);
        *raiz = nova_raiz;
    }
}

void arvB_imprime_pais(NoArvB* no, int nivel, int posicao) {
    if (no == NULL) {
        return;
    }

    if (!no->folha) {
        printf("No pai (Nivel %d, Posicao %d): ", nivel, posicao);
        for (int i = 0; i < no->num_chaves; i++) {
            printf("%d ", no->chaves[i]);
        }
        printf("\n");
    }

    for (int i = 0; i <= no->num_chaves; i++) {
        arvB_imprime_pais(no->filho[i], nivel + 1, i);
    }
}

void arvB_imprime_pais_nivel(ArvB raiz) {
    arvB_imprime_pais(raiz, 0, 0);
}

void arvB_imprime_folhas(NoArvB* no, int nivel, int posicao) {
    if (no == NULL) {
        return;
    }

    if (no->folha) {
        printf("No folha (Nivel %d, Posicao %d): ", nivel, posicao);
        for (int i = 0; i < no->num_chaves; i++) {
            printf("%d ", no->chaves[i]);
        }
        printf("\n");
    } else {
        for (int i = 0; i <= no->num_chaves; i++) {
            arvB_imprime_folhas(no->filho[i], nivel + 1, i);
        }
    }
}

void arvB_imprime_folhas_nivel(ArvB raiz) {
    arvB_imprime_folhas(raiz, 0, 0);
}

int arvB_busca_chave(ArvB no, int chave) {
    if (no == NULL) {
        return 0;
    }

    int posicao = 0;
    while (posicao < no->num_chaves && chave > no->chaves[posicao]) {
        posicao++;
    }

    if (posicao < no->num_chaves && chave == no->chaves[posicao]) {
        printf("Valor %d encontrado!\n\n", chave);
        return 1;
    }

    if (no->folha) {
        printf("Valor %d nao encontrado!\n\n", chave);
        return 0;
    }

    return arvB_busca_chave(no->filho[posicao], chave);
}

int arvB_busca(ArvB raiz, int valor) {
    if (raiz == NULL) {
        return 0;
    }
    return arvB_busca_chave(raiz, valor);
}

int arvB_qtd_nos_recursivo(ArvB no) {
    if (no == NULL) {
        return 0;
    }

    int cont = 1;
    for (int i = 0; i <= no->num_chaves; i++) {
        cont += arvB_qtd_nos_recursivo(no->filho[i]);               
    }
    return cont;
}

int arvB_qtd_nos(ArvB raiz) {
    if (raiz == NULL) {
        return 0;
    }  
    return arvB_qtd_nos_recursivo(raiz);
}

int arvB_qtd_chaves_recursivo(ArvB no) {
    if (no == NULL) {
        return 0;
    }

    int cont = no->num_chaves; 
    
    for (int i = 0; i <= no->num_chaves; i++) {
        cont = cont + arvB_qtd_chaves_recursivo(no->filho[i]);            
    }
    return cont;
}

int arvB_qtd_chaves(ArvB raiz) {
    if (raiz == NULL) {
        return 0;
    }   
    return arvB_qtd_chaves_recursivo(raiz);
}