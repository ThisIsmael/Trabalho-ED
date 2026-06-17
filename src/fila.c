#include <stdio.h>
#include <stdlib.h>
#include "../headers/fila.h"

Fila *criarFila() {
    Fila *fila = (Fila *)malloc(sizeof(Fila));

    if (fila != NULL) {
        fila->inicio = NULL;
        fila->fim = NULL;
    }

    return fila;
}

int filaVazia(Fila *fila) {
    return (fila == NULL || fila->inicio == NULL);
}

void enfileirarReserva(Fila *fila, Reserva reserva) {

    NoFila *novo = (NoFila *)malloc(sizeof(NoFila));

    if (novo == NULL) {
        printf("Erro de alocacao de memoria!\n");
        return;
    }

    novo->reserva = reserva;
    novo->proximo = NULL;

    if (filaVazia(fila)) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->proximo = novo;
        fila->fim = novo;
    }
}

Reserva desenfileirarReserva(Fila *fila) {

    Reserva reservaVazia = {"", -1};

    if (filaVazia(fila)) {
        printf("Fila vazia!\n");
        return reservaVazia;
    }

    NoFila *temp = fila->inicio;
    Reserva reservaRemovida = temp->reserva;

    fila->inicio = temp->proximo;

    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }

    free(temp);

    return reservaRemovida;
}

void exibirReservas(Fila *fila) {

    if (filaVazia(fila)) {
        printf("\nNenhuma reserva na fila.\n");
        return;
    }

    NoFila *atual = fila->inicio;

    printf("\n===== FILA DE RESERVAS =====\n");

    while (atual != NULL) {
        printf("Usuario: %s\n", atual->reserva.nomeUsuario);
        printf("Codigo do livro: %d\n", atual->reserva.codigoLivro);
        printf("----------------------------\n");

        atual = atual->proximo;
    }
}

void liberarFila(Fila *fila) {
    while (!filaVazia(fila)) {
        desenfileirarReserva(fila);
    }

    free(fila);
}