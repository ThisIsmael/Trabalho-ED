#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/livro.h"

Livro* criarLivro(int codigo, char titulo[], char autor[],
                  int ano, int quantidadeTotal)
{
    Livro* livro = (Livro*) malloc(sizeof(Livro));
    if (livro == NULL) {
        fprintf(stderr, "Erro: memoria insuficiente para criar livro.\n");
        exit(EXIT_FAILURE);
    }

    livro->codigo = codigo;
    livro->ano = ano;
    livro->quantidadeTotal = quantidadeTotal;
    livro->quantidadeDisponivel = quantidadeTotal; 

    int i;
    
    for (i = 0; i < (int)(sizeof(livro->titulo) - 1) && titulo[i] != '\0'; i++)
        livro->titulo[i] = titulo[i];
    livro->titulo[i] = '\0';

    for (i = 0; i < (int)(sizeof(livro->autor) - 1) && autor[i] != '\0'; i++)
        livro->autor[i] = autor[i];
    livro->autor[i] = '\0';

    return livro;
}

void exibirLivro(Livro* livro)
{
    if (livro == NULL) {
        printf("Livro invalido.\n");
        return;
    }

    printf("--------------------------------------------------\n");
    printf("Codigo: %d\n",  livro->codigo);
    printf("Titulo: %s\n",  livro->titulo);
    printf("Autor: %s\n",  livro->autor);
    printf("Ano: %d\n",  livro->ano);
    printf("Total: %d exemplar(es)\n", livro->quantidadeTotal);
    printf("Disponivel: %d exemplar(es)\n", livro->quantidadeDisponivel);
    printf("--------------------------------------------------\n");
}

int obterCodigoLivro(Livro* livro)
{
    if (livro == NULL) return -1;
    return livro->codigo;
}

int obterQuantidadeDisponivel(Livro* livro)
{
    if (livro == NULL) return 0;
    return livro->quantidadeDisponivel;
}

void emprestarExemplar(Livro* livro)
{
    if (livro == NULL) return;

    if (livro->quantidadeDisponivel > 0) {
        livro->quantidadeDisponivel--; // diminuir quantidadeDisponivel
    } else {
        printf("Aviso: nenhum exemplar disponivel para emprestimo.\n");
    }
}


void devolverExemplar(Livro* livro)
{
    if (livro == NULL) return;

    if (livro->quantidadeDisponivel < livro->quantidadeTotal) {
        livro->quantidadeDisponivel++; //Incrementa a quantidadeDisponivel em 1,mas não pode passar da quantidadeTotal
    } else {
        printf("Aviso: todos os exemplares ja estao na biblioteca.\n");
    }
}
