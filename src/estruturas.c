#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"

/* ==========================================================================
   1. LISTA ENCADEADA SIMPLES (TAD)
   ========================================================================== */

ListaEncadeada* lista_criar() {
    ListaEncadeada* lista = (ListaEncadeada*)malloc(sizeof(ListaEncadeada));
    if (lista != NULL) {
        lista->inicio = NULL;
        lista->tamanho = 0;
    }
    return lista;
}

void lista_destruir(ListaEncadeada* lista) {
    if (lista != NULL) {
        NodeLista* atual = lista->inicio;
        while (atual != NULL) {
            NodeLista* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
        free(lista);
    }
}

bool lista_vazia(ListaEncadeada* lista) {
    if (lista == NULL) return true;
    return lista->tamanho == 0;
}

int lista_tamanho(ListaEncadeada* lista) {
    if (lista == NULL) return -1;
    return lista->tamanho;
}

bool lista_inserir_inicio(ListaEncadeada* lista, int valor) {
    if (lista == NULL) return false;
    NodeLista* novo_no = (NodeLista*)malloc(sizeof(NodeLista));
    if (novo_no == NULL) return false;
    novo_no->dado = valor;
    novo_no->proximo = lista->inicio;
    lista->inicio = novo_no;
    lista->tamanho++;
    return true;
}

bool lista_inserir_fim(ListaEncadeada* lista, int valor) {
    if (lista == NULL) return false;
    NodeLista* novo_no = (NodeLista*)malloc(sizeof(NodeLista));
    if (novo_no == NULL) return false;
    novo_no->dado = valor;
    novo_no->proximo = NULL;

    if (lista->inicio == NULL) {
        lista->inicio = novo_no;
    } else {
        NodeLista* atual = lista->inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo_no;
    }
    lista->tamanho++;
    return true;
}

bool lista_remover(ListaEncadeada* lista, int valor) {
    if (lista == NULL || lista->inicio == NULL) return false;

    NodeLista* atual = lista->inicio;
    NodeLista* anterior = NULL;

    while (atual != NULL && atual->dado != valor) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) return false; // Não encontrou

    if (anterior == NULL) {
        lista->inicio = atual->proximo; // Remove do início
    } else {
        anterior->proximo = atual->proximo; // Remove do meio/fim
    }

    free(atual);
    lista->tamanho--;
    return true;
}

bool lista_buscar(ListaEncadeada* lista, int valor) {
    if (lista == NULL) return false;
    NodeLista* atual = lista->inicio;
    while (atual != NULL) {
        if (atual->dado == valor) return true;
        atual = atual->proximo;
    }
    return false;
}

void lista_imprimir(ListaEncadeada* lista) {
    if (lista == NULL) return;
    NodeLista* atual = lista->inicio;
    printf("Lista: [ ");
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }
    printf("]");
}


/* ==========================================================================
   2. FILA DINÂMICA (TAD)
   ========================================================================== */

Fila* fila_criar() {
    Fila* fila = (Fila*)malloc(sizeof(Fila));
    if (fila != NULL) {
        fila->frente = NULL;
        fila->r_fim = NULL;
        fila->tamanho = 0;
    }
    return fila;
}

void fila_destruir(Fila* fila) {
    if (fila != NULL) {
        NodeFila* atual = fila->frente;
        while (atual != NULL) {
            NodeFila* proximo = atual->proximo;
            free(atual);
            atual = proximo;
        }
        free(fila);
    }
}

bool fila_vazia(Fila* fila) {
    if (fila == NULL) return true;
    return fila->tamanho == 0;
}

int fila_tamanho(Fila* fila) {
    if (fila == NULL) return -1;
    return fila->tamanho;
}

bool fila_enfileirar(Fila* fila, int valor) {
    if (fila == NULL) return false;
    NodeFila* novo_no = (NodeFila*)malloc(sizeof(NodeFila));
    if (novo_no == NULL) return false;
    novo_no->dado = valor;
    novo_no->proximo = NULL;

    if (fila->r_fim == NULL) {
        fila->frente = novo_no;
    } else {
        fila->r_fim->proximo = novo_no;
    }
    fila->r_fim = novo_no;
    fila->tamanho++;
    return true;
}

bool fila_desenfileirar(Fila* fila, int* valor_retorno) {
    if (fila == NULL || fila->frente == NULL) return false;
    
    NodeFila* no_removido = fila->frente;
    if (valor_retorno != NULL) {
        *valor_retorno = no_removido->dado;
    }

    fila->frente = no_removido->proximo;
    if (fila->frente == NULL) {
        fila->r_fim = NULL; // Fila ficou vazia
    }

    free(no_removido);
    fila->tamanho--;
    return true;
}

void fila_imprimir(Fila* fila) {
    if (fila == NULL) return;
    NodeFila* atual = fila->frente;
    printf("Fila: [ ");
    while (atual != NULL) {
        printf("%d ", atual->dado);
        atual = atual->proximo;
    }
    printf("]");

}


/* ==========================================================================
   3. ÁRVORE BINÁRIA DE BUSCA - BST (TAD)
   ========================================================================== */

ArvoreBST* bst_criar() {
    ArvoreBST* arvore = (ArvoreBST*)malloc(sizeof(ArvoreBST));
    if (arvore != NULL) {
        arvore->raiz = NULL;
    }
    return arvore;
}

/* Função auxiliar para liberar os nós recursivamente */
static void liberar_nos_bst(NodeBST* no) {
    if (no != NULL) {
        liberar_nos_bst(no->esquerdo);
        liberar_nos_bst(no->direito);
        free(no);
    }
}

void bst_destruir(ArvoreBST* arvore) {
    if (arvore != NULL) {
        liberar_nos_bst(arvore->raiz);
        free(arvore);
    }
}

bool bst_vazia(ArvoreBST* arvore) {
    if (arvore == NULL) return true;
    return arvore->raiz == NULL;
}

/* Função auxiliar para inserção recursiva */
static NodeBST* inserir_no_bst(NodeBST* no, int chave, bool* inserido) {
    if (no == NULL) {
        NodeBST* novo_no = (NodeBST*)malloc(sizeof(NodeBST));
        if (novo_no == NULL) return NULL;
        novo_no->chave = chave;
        novo_no->esquerdo = NULL;
        novo_no->direito = NULL;
        *inserido = true;
        return novo_no;
    }
    if (chave < no->chave) {
        no->esquerdo = inserir_no_bst(no->esquerdo, chave, inserido);
    } else if (chave > no->chave) {
        no->direito = inserir_no_bst(no->direito, chave, inserido);
    }
    return no;
}

bool bst_inserir(ArvoreBST* arvore, int chave) {
    if (arvore == NULL) return false;
    bool inserido = false;
    arvore->raiz = inserir_no_bst(arvore->raiz, chave, &inserido);
    return inserido;
}

/* Função auxiliar para encontrar o menor nó (usado na remoção) */
static NodeBST* encontrar_minimo(NodeBST* no) {
    NodeBST* atual = no;
    while (atual && atual->esquerdo != NULL) {
        atual = atual->esquerdo;
    }
    return atual;
}

/* Função auxiliar para remoção recursiva */
static NodeBST* remover_no_bst(NodeBST* no, int chave, bool* removido) {
    if (no == NULL) return NULL;

    if (chave < no->chave) {
        no->esquerdo = remover_no_bst(no->esquerdo, chave, removido);
    } else if (chave > no->chave) {
        no->direito = remover_no_bst(no->direito, chave, removido);
    } else {
        *removido = true;
        // Caso 1 e 2: Sem filhos ou com um filho
        if (no->esquerdo == NULL) {
            NodeBST* temp = no->direito;
            free(no);
            return temp;
        } else if (no->direito == NULL) {
            NodeBST* temp = no->esquerdo;
            free(no);
            return temp;
        }
        // Caso 3: Dois filhos - Encontra o sucessor in-order (menor da subárvore direita)
        NodeBST* temp = encontrar_minimo(no->direito);
        no->chave = temp->chave;
        no->direito = remover_no_bst(no->direito, temp->chave, removido);
    }
    return no;
}

bool bst_remover(ArvoreBST* arvore, int chave) {
    if (arvore == NULL) return false;
    bool removido = false;
    arvore->raiz = remover_no_bst(arvore->raiz, chave, &removido);
    return removido;
}

bool bst_buscar(ArvoreBST* arvore, int chave) {
    if (arvore == NULL) return false;
    NodeBST* atual = arvore->raiz;
    while (atual != NULL) {
        if (chave == atual->chave) return true;
        else if (chave < atual->chave) atual = atual->esquerdo;
        else atual = atual->direito;
    }
    return false;
}

/* Funções auxiliares para percursos */
static void em_ordem(NodeBST* no) {
    if (no != NULL) {
        em_ordem(no->esquerdo);
        printf("%d ", no->chave);
        em_ordem(no->direito);
    }
}

static void pre_ordem(NodeBST* no) {
    if (no != NULL) {
        printf("%d ", no->chave);
        pre_ordem(no->esquerdo);
        pre_ordem(no->direito);
    }
}

static void pos_ordem(NodeBST* no) {
    if (no != NULL) {
        pos_ordem(no->esquerdo);
        pos_ordem(no->direito);
        printf("%d ", no->chave);
    }
}

void bst_em_ordem(ArvoreBST* arvore) {
    if (arvore == NULL) return;
    printf("Em Ordem: [ ");
    em_ordem(arvore->raiz);
    printf("]");

}

void bst_pre_ordem(ArvoreBST* arvore) {
    if (arvore == NULL) return;
    printf("Pré Ordem: [ ");
    pre_ordem(arvore->raiz);
    printf("]");
}

void bst_pos_ordem(ArvoreBST* arvore) {
    if (arvore == NULL) return;
    printf("Pós Ordem: [ ");
    pos_ordem(arvore->raiz);
    printf("]");
}
