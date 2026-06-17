#include <stdio.h>
#include <stdlib.h>
#include "../headers/lista.h"

Lista *criarLista() {

    Lista *lista = (Lista *)malloc(sizeof(Lista));

    if (lista != NULL) {
        lista->inicio = NULL;
    }

    return lista;
}

int listaVazia(Lista *lista) {
    return (lista == NULL || lista->inicio == NULL);
}

void inserirEmprestimo(Lista *lista, Emprestimo emprestimo) {

    NoLista *novo = (NoLista *)malloc(sizeof(NoLista));

    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }

    novo->emprestimo = emprestimo;

    // Inserção no início da lista
    novo->proximo = lista->inicio;
    lista->inicio = novo;
}

void listarEmprestimos(Lista *lista) {

    if (listaVazia(lista)) {
        printf("\nNenhum emprestimo registrado.\n");
        return;
    }

    NoLista *atual = lista->inicio;

    printf("\n===== HISTORICO DE EMPRESTIMOS =====\n");

    while (atual != NULL) {

        printf("Usuario: %s\n",
               atual->emprestimo.nomeUsuario);

        printf("Codigo do livro: %d\n",
               atual->emprestimo.codigoLivro);

        printf("Titulo do livro: %s\n",
               atual->emprestimo.tituloLivro);

        printf("------------------------------------\n");

        atual = atual->proximo;
    }
}

void liberarLista(Lista *lista) {

    NoLista *atual = lista->inicio;

    while (atual != NULL) {

        NoLista *temp = atual;
        atual = atual->proximo;

        free(temp);
    }

    free(lista);
}