#ifndef LIVRO_H
#define LIVRO_H

//TAD Livro - Representa um livro na biblioteca, com informações e controle de estoque.

typedef struct {
    int  codigo;  // id do livro          
    char titulo[100];                                  
    char autor[100];                                 
    int  ano;  // ano de publicação                     
    int  quantidadeTotal;  // total de livros na biblioteca    
    int  quantidadeDisponivel; // disponíveis para empréstimo
} Livro;


Livro* criarLivro(int codigo, char titulo[], char autor[],
                  int ano, int quantidadeTotal);

void exibirLivro(Livro* livro);

int obterCodigoLivro(Livro* livro);

int obterQuantidadeDisponivel(Livro* livro);

void emprestarExemplar(Livro* livro);

void devolverExemplar(Livro* livro);

#endif 
