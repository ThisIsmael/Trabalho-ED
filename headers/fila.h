#ifndef FILA_H
#define FILA_H

typedef struct Reserva {
    char nomeUsuario[100];
    int codigoLivro;
} Reserva;

typedef struct NoFila {
    Reserva reserva;
    struct NoFila *proximo;
} NoFila;

typedef struct Fila {
    NoFila *inicio;
    NoFila *fim;
} Fila;

// Operações da fila
Fila *criarFila();

void enfileirarReserva(Fila *fila, Reserva reserva);

Reserva desenfileirarReserva(Fila *fila);

int filaVazia(Fila *fila);

void exibirReservas(Fila *fila);

void liberarFila(Fila *fila);

#endif