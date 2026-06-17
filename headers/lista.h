#ifndef LISTA_H
#define LISTA_H

typedef struct Emprestimo {
    char nomeUsuario[100];
    int codigoLivro;
    char tituloLivro[100];
} Emprestimo;

typedef struct NoLista {
    Emprestimo emprestimo;
    struct NoLista *proximo;
} NoLista;

typedef struct Lista {
    NoLista *inicio;
} Lista;

// Operações da lista
Lista *criarLista();

void inserirEmprestimo(Lista *lista, Emprestimo emprestimo);

void listarEmprestimos(Lista *lista);

int listaVazia(Lista *lista);

void liberarLista(Lista *lista);

#endif