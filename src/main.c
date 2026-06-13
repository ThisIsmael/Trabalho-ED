#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/livro.h"
#include "livro.c"
// #include "../headers/abbl.h"

// para impedir que seja passado caracteres invalidos para opções que exigem numero como entrada
int lerIntInputMenu(const char *mensagem) {
    int valor;
    printf("%s", mensagem);
    while (scanf("%d", &valor) != 1) {
        printf("Entrada invalida! Digite um numero:");
        while (getchar() != '\n');
    }
    getchar();
    return valor;
}

int lerIntInputInfo(const char *mensagem) {
    int valor;
    printf("%s", mensagem);
    while (scanf("%d", &valor) != 1) {
        printf("Entrada invalida! Digite com número(s):");
        while (getchar() != '\n');
    }
    getchar();
    return valor;
}


int main()
{
    int opcao;

    do {
    printf("Bem-vindo à Biblioteca! \n");
    printf("1. Cadastrar Livro \n");
    printf("2. Buscar Livro por ID \n");
    printf("3. Listar Livros \n");
    printf("4. Emprestar Livro \n");
    printf("5. Devolver Livro \n");
    printf("6. Exibir fila de reservas \n");
    printf("7. Exibir historico de emprestimos \n");
    printf("8. Exibir quantidade de livros cadastrados \n");
    printf("9. Exibir altura da arvore \n");
    printf("0. Sair \n");
    opcao = lerIntInputMenu("Escolha uma opcao (apenas numeros): ");
   

        switch (opcao) {
            case 1:
                int codigo = lerIntInputInfo("Digite o codigo do livro (apenas números): ");
                printf("Digite o titulo do livro: ");   
                char titulo[100];
                fgets(titulo, sizeof(titulo), stdin); 
                titulo[strcspn(titulo, "\n")] = '\0';
                printf("Digite o autor do livro: ");
                char autor[100];
                fgets(autor, sizeof(autor), stdin);
                autor[strcspn(autor, "\n")] = '\0';
                int ano = lerIntInputInfo("Digite o ano do livro: ");
                int quantidadeTotal = lerIntInputInfo("Digite a quantidade total de exemplares: ");
            // Código para cadastrar livro
                break;
            case 2:
                // Código para buscar livro por ID
                break;
            case 3:
                int subopcao;
                printf("a. Listar em ordem crescente\n");
                printf("b. Listar em pré-ordem\n");
                printf("c. Listar em pós-ordem\n");
                printf("Escolha uma opção: ");
                scanf(" %c", &subopcao); getchar();

                switch (subopcao) {
                /*case 'a': listarLivrosEmOrdem(abbl);   break;
                case 'b': listarLivrosPreOrdem(abbl);  break;
                case 'c': listarLivrosPosOrdem(abbl);  break;
                default: printf("Opcao invalida!\n");*/
                }
                break;
            case 4:
                // Código para emprestar livro
                break;
            case 5:
                // Código para devolver livro
                break;
            case 6:
                // Exibir fila de reservas
            
                break;
            case 7:
                // Exibir historico de emprestimos
               
                break;
            case 8:
                // Exibir quantidade de livros cadastrados
        
                break;
            case 9:
                // Exibir altura da arvore
    
                break;
            case 0:
                printf("Saindo do programa. Ate logo!\n");
                break;
            default:
                printf("Opção inválida. Por favor, tente novamente.\n");
        
        } 
    } while (opcao != 0);

    return 0;
}