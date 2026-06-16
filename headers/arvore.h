/**
 * @file arvore.h
 * @brief Definição de Tipos Abstratos de Dados (TAD) em C: Árvore Binária de Busca para Livros.
 * Este arquivo contém as estruturas de dados e os protótipos de funções seguindo o conceito de TAD (Tipo Abstrato de Dados).
 */

#ifndef ARVORE_H
#define ARVORE_H
#include <stdbool.h>
#include "livro.h"

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
void removerLivroArvore ( Arvore * arvore , int codigo ) ;
Livro * buscarLivroArvore ( Arvore * arvore , int codigo ) ;
void buscarLivrosPorTituloOuAutor ( Arvore * arvore , const char * termo ) ;
void listarLivrosEmOrdem ( Arvore * arvore ) ;
void listarLivrosPreOrdem ( Arvore * arvore ) ;
void listarLivrosPosOrdem ( Arvore * arvore ) ;
int contarLivros ( Arvore * arvore ) ;
int calcularAlturaArvore ( Arvore * arvore ) ;
void liberarArvore ( Arvore * arvore ) ;

#endif /* ABBL_H */
