/**
 * @file estruturas.h
 * @brief Definição de Tipos Abstratos de Dados (TAD) em C: Lista Encadeada, Fila e Árvore Binária de Busca.
 * * Este arquivo contém as estruturas de dados e os protótipos de funções para cada uma delas,
 * seguindo o conceito de TAD (Tipo Abstrato de Dados).
 */

#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

#include <stdbool.h>

/* ==========================================================================
   1. LISTA ENCADEADA SIMPLES (TAD)
   ========================================================================== */

/** @brief Nó da Lista Encadeada */
typedef struct NodeLista {
    int dado;                   /**< Valor armazenado no nó */
    struct NodeLista* proximo;  /**< Ponteiro para o próximo nó */
} NodeLista;

/** @brief Estrutura de controle da Lista Encadeada */
typedef struct {
    NodeLista* inicio;          /**< Ponteiro para o primeiro elemento */
    int tamanho;                /**< Quantidade de elementos na lista */
} ListaEncadeada;

/* Protótipos das Funções da Lista */
ListaEncadeada* lista_criar();
void lista_destruir(ListaEncadeada* lista);
bool lista_vazia(ListaEncadeada* lista);
int lista_tamanho(ListaEncadeada* lista);
bool lista_inserir_inicio(ListaEncadeada* lista, int valor);
bool lista_inserir_fim(ListaEncadeada* lista, int valor);
bool lista_remover(ListaEncadeada* lista, int valor);
bool lista_buscar(ListaEncadeada* lista, int valor);
void lista_imprimir(ListaEncadeada* lista);


/* ==========================================================================
   2. FILA DINÂMICA (TAD)
   ========================================================================== */

/** @brief Nó da Fila */
typedef struct NodeFila {
    int dado;                   /**< Valor armazenado no nó */
    struct NodeFila* proximo;   /**< Ponteiro para o próximo nó da fila */
} NodeFila;

/** @brief Estrutura de controle da Fila */
typedef struct {
    NodeFila* frente;           /**< Ponteiro para o início (onde remove) */
    NodeFila* r_fim;            /**< Ponteiro para o fim (onde insere) */
    int tamanho;                /**< Quantidade de elementos na fila */
} Fila;

/* Protótipos das Funções da Fila */
Fila* fila_criar();
void fila_destruir(Fila* fila);
bool fila_vazia(Fila* fila);
int fila_tamanho(Fila* fila);
bool fila_enfileirar(Fila* fila, int valor);
bool fila_desenfileirar(Fila* fila, int* valor_retorno);
void fila_imprimir(Fila* fila);


/* ==========================================================================
   3. ÁRVORE BINÁRIA DE BUSCA - BST (TAD)
   ========================================================================== */

/** @brief Nó da Árvore Binária de Busca */
typedef struct NodeBST {
    int chave;                  /**< Chave/Valor do nó */
    struct NodeBST* esquerdo;   /**< Ponteiro para a subárvore esquerda (menores) */
    struct NodeBST* direito;    /**< Ponteiro para a subárvore direita (maiores) */
} NodeBST;

/** @brief Estrutura de controle da Árvore Binária de Busca */
typedef struct {
    NodeBST* raiz;              /**< Ponteiro para a raiz da árvore */
} ArvoreBST;

/* Protótipos das Funções da Árvore */
ArvoreBST* bst_criar();
void bst_destruir(ArvoreBST* arvore);
bool bst_vazia(ArvoreBST* arvore);
bool bst_inserir(ArvoreBST* arvore, int chave);
bool bst_remover(ArvoreBST* arvore, int chave);
bool bst_buscar(ArvoreBST* arvore, int chave);

/* Percursos na Árvore */
void bst_em_ordem(ArvoreBST* arvore);
void bst_pre_ordem(ArvoreBST* arvore);
void bst_pos_ordem(ArvoreBST* arvore);

#endif /* ESTRUTURAS_H */
