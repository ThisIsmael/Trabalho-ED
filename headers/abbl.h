/**
 * @file abbl.h
 * @brief Definição de Tipos Abstratos de Dados (TAD) em C: Árvore Binária de Busca para Livros.
 * Este arquivo contém as estruturas de dados e os protótipos de funções seguindo o conceito de TAD (Tipo Abstrato de Dados).
 */

#ifndef ABBL_H
#define ABBL_H
#include <stdbool.h>

/** @brief Estrutura que representa um Livro */
typedef struct {
    int codigo;
    char titulo[100];
    char autor[100];
    int ano_publicacao;
} Livro;

/** @brief Nó da Árvore de Livros */
typedef struct NodeArvore {
    Livro* livro;
    struct NodeArvore* esquerdo;
    struct NodeArvore* direito;
} NodeArvore;

/** @brief Estrutura de controle da Árvore de Livros */
typedef struct {
    NodeArvore* raiz;
} Arvore;

void inserirLivroArvore ( Arvore * arvore , Livro * livro ) ;
Livro * buscarLivroArvore ( Arvore * arvore , int codigo ) ;
void listarLivrosEmOrdem ( Arvore * arvore ) ;
void listarLivrosPreOrdem ( Arvore * arvore ) ;
void listarLivrosPosOrdem ( Arvore * arvore ) ;
int contarLivros ( Arvore * arvore ) ;
int calcularAlturaArvore ( Arvore * arvore ) ;

#endif /* ABBL_H */
