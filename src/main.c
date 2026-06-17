#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "../headers/livro.h"   
#include "../headers/arvore.h"    
#include "../headers/fila.h"    
#include "../headers/lista.h"  


// para impedir que seja passado caracteres invalidos para opções que exigem numero como entrada
int lerIntInputMenu(const char *mensagem) {
    int valor;
    printf("%s", mensagem);
    while (scanf("%d", &valor) != 1) {
        printf("Entrada invalida! Digite um numero:");
        while (getchar() != '\n'); // limpa o buffer do teclado
    }
    while (getchar() != '\n'); // descarta tudo que ficou no buffer apos o numero digitado
    return valor;
}

void esperarEnter(){
    printf("\nPressione Enter para continuar...");
    getchar();
}

int lerIntInputInfo(const char *mensagem) {
    int valor;
    printf("%s", mensagem);
    while (scanf("%d", &valor) != 1) {
        printf("Entrada invalida! Digite com numero(s):");
        while (getchar() != '\n'); // limpa o buffer do teclado 
    }
    while (getchar() != '\n'); // descarta tudo que ficou no buffer apos o numero digitado 
    return valor;
}
int main()
{
    // aqui vão ser Inicializadas as tres estruturas de dados principais do sistema (arvore, lista, fila) 
    Arvore arvore = {NULL};        
    Fila *fila = criarFila();      
    Lista *historico = criarLista(); 
    int opcao;

    do {
        //opções que vão ser disponibilizadas no menu principal do sistema para o usuário escolher a ação desejada
        printf("\nBem-vindo a Biblioteca!\n");
        printf("1.  Cadastrar Livro\n");
        printf("2.  Buscar Livro por codigo\n");
        printf("3.  Listar Livros em ordem crescente\n");
        printf("4.  Listar Livros em pre-ordem\n");
        printf("5.  Listar Livros em pos-ordem\n");
        printf("6.  Emprestar Livro\n");
        printf("7.  Devolver Livro\n");
        printf("8.  Exibir fila de reservas\n");
        printf("9.  Exibir historico de emprestimos\n");
        printf("10. Exibir quantidade de livros cadastrados\n");
        printf("11. Exibir altura da arvore\n");
        printf("12. Remover livro\n");
        printf("13. Buscar livro por titulo ou autor\n");
        printf("0.  Sair\n");
        opcao = lerIntInputMenu("Escolha uma opcao (apenas numeros): ");

        switch (opcao) {
            case 1: {
                int codigo = lerIntInputInfo("Digite o codigo do livro (apenas numeros): ");

                //primeiro vai ser verificado se ja existe um livro com esse codigo na arvore 
                if (buscarLivroArvore(&arvore, codigo) != NULL) {
                    printf("Erro: Impossivel cadastrar este livro. Ja existe um livro com codigo %d.\n", codigo);
                    esperarEnter();
                    break;
                }

                // Coleta os demais dados do livro: titulo, autor, ano de publicacao e quantidade total de exemplares
                printf("Digite o titulo do livro: ");
                char titulo[100];
                fgets(titulo, sizeof(titulo), stdin);
                titulo[strcspn(titulo, "\n")] = '\0'; //remove o '\n' do final da string 

                printf("Digite o autor do livro: ");
                char autor[100];
                fgets(autor, sizeof(autor), stdin);
                autor[strcspn(autor, "\n")] = '\0'; 

                int ano = lerIntInputInfo("Digite o ano do livro: ");
                int quantidadeTotal = lerIntInputInfo("Digite a quantidade total de exemplares: ");

                // aqui o livro vai ser criado e inserido na arvore binaria de busca */
                Livro* livro = criarLivro(codigo, titulo, autor, ano, quantidadeTotal);
                inserirLivroArvore(&arvore, livro);

                printf("Livro cadastrado com sucesso!\n");
                esperarEnter();
                break;
            }

            case 2: {
                int codigoBusca = lerIntInputInfo("Digite o codigo do livro: ");
                Livro* livroEncontrado = buscarLivroArvore(&arvore, codigoBusca);

                if (livroEncontrado != NULL) {
                    printf("Livro encontrado!\n");
                    exibirLivro(livroEncontrado); // exibe todos os dados do livro (estrutura montada em livro.c)
                } else {
                    printf("Livro com codigo %d nao encontrado.\n", codigoBusca);
                }
                esperarEnter();
                break;
            }

        
            case 3:
            // Listar livros em ordem crescente de codigo 
                listarLivrosEmOrdem(&arvore);
                esperarEnter();
                break;

            case 4:
            // Listar livros em pre-ordem (raiz, esquerda, direita)
                listarLivrosPreOrdem(&arvore);
                esperarEnter();
                break;

            case 5:
              // Listar livros em pos-ordem (esquerda, direita, raiz)
                listarLivrosPosOrdem(&arvore);
                esperarEnter();
                break;

            case 6: {
                //emprestar livro
                char nomeUsuario[100];
                printf("Digite o nome do usuario: ");
                fgets(nomeUsuario, sizeof(nomeUsuario), stdin);
                nomeUsuario[strcspn(nomeUsuario, "\n")] = '\0'; /* remove o '\n' do final */

                int codigoEmp = lerIntInputInfo("Digite o codigo do livro que deseja emprestar: ");
                Livro* livroEmprestimo = buscarLivroArvore(&arvore, codigoEmp);

                if (livroEmprestimo == NULL) {
                    // Livro nao existe na arvore
                    printf("Impossivel emprestar! O livro com codigo %d nao foi encontrado.\n", codigoEmp);
                } else if (obterQuantidadeDisponivel(livroEmprestimo) > 0) {
                    // se tem exemplares disponiveis = realiza o emprestimo
                    emprestarExemplar(livroEmprestimo); // reduz a quantidade disponivel

                    // Registra o emprestimo no historico (na lista encadeada)
                    Emprestimo emp;
                    strcpy(emp.nomeUsuario, nomeUsuario);
                    emp.codigoLivro = codigoEmp;
                    strcpy(emp.tituloLivro, livroEmprestimo->titulo);
                    inserirEmprestimo(historico, emp);

                    printf("Livro emprestado com sucesso!\n");
                } else {
                    // quando não tem exemplares disponiveis: oferece entrada na fila de reservas
                    printf("Nenhum exemplar disponivel.\n");
                    printf("Deseja entrar na fila de reservas?\n");
                    printf("1. Sim\n"); // assim vai cair no primeiro if e criar a reserva para o usuario
                    printf("2. Nao\n");
                    int resposta = lerIntInputMenu("Escolha uma opcao: ");

                    if (resposta == 1) {
                        // Cria a reserva e adiciona ao final da fila(fifo)
                        Reserva reserva;
                        strcpy(reserva.nomeUsuario, nomeUsuario);
                        reserva.codigoLivro = codigoEmp;
                        enfileirarReserva(fila, reserva);
                        printf("Usuario inserido na fila de reservas!\n");
                    }
                }
                esperarEnter();
                break;
            }

       
            case 7: {
                //devolver livro
                int codigoDevolver = lerIntInputInfo("Digite o codigo do livro que deseja devolver: ");
                Livro* livroDevolucao = buscarLivroArvore(&arvore, codigoDevolver);

                if (livroDevolucao == NULL) {
                    //caso não exista livro na arvore com o codigo informado, não tem como devolver
                    printf("Impossivel devolver! O livro com codigo %d nao foi encontrado.\n", codigoDevolver);
                } else {
                    devolverExemplar(livroDevolucao); //aumenta a quantidade disponivel 
                    printf("O livro com codigo %d foi devolvido com sucesso!\n", codigoDevolver);

                    // Percorre a fila para verificar se tem alguem aguardando o livro informado
                    if (!filaVazia(fila)) {
                        NoFila *atual = fila->inicio;
                        int temReserva = 0;
                        while (atual != NULL) {
                            if (atual->reserva.codigoLivro == codigoDevolver) {
                                temReserva = 1;
                                break;
                            }
                            atual = atual->proximo; // vai para o proximo no da fila
                        }
                        // Avisa a quem está mexendo no sistema que tem usuarios na fila para este livro
                        if (temReserva) {
                            printf("Aviso: Ha usuarios aguardando na fila de reservas para este livro.\n");
                            printf("Use a opcao 8 para visualizar a fila de reservas.\n");
                        }
                    }
                }
                esperarEnter();
                break;
            }

            case 8:
            //Exibir todos os usuarios na fila de reservas
                exibirReservas(fila);
                esperarEnter();
                break;

            case 9:
            //Exibir historico completo de emprestimos realizados
                listarEmprestimos(historico);
                esperarEnter();
                break;

            case 10:
            //Exibir total de livros cadastrados na arvore
                printf("Quantidade de livros cadastrados: %d\n", contarLivros(&arvore));
                esperarEnter();
                break;

            case 11:
             //Exibir a altura da arvore binaria de busca
                printf("Altura da arvore: %d\n", calcularAlturaArvore(&arvore));
                esperarEnter();
                break;

            case 12:
            //Remover livro da arvore
                int codigoRemover = lerIntInputInfo("Digite o codigo do livro que deseja remover: ");
                removerLivroArvore(&arvore, codigoRemover);
                printf("Livro com codigo %d removido com sucesso!\n", codigoRemover);
                esperarEnter();
                break;

            case 13: {
            //Buscar livro por titulo ou autor
                char termoBusca[100];
                printf("Digite o titulo ou autor (ou parte deles) para busca: ");
                fgets(termoBusca, sizeof(termoBusca), stdin);
                termoBusca[strcspn(termoBusca, "\n")] = '\0';
                buscarLivrosPorTituloOuAutor(&arvore, termoBusca);
                esperarEnter();
                break;
            }

            case 0:
            //Encerra a execução do programa
                printf("Saindo do programa. Ate logo!\n");
                break;

            default:
            //caso não tenha a opção digitada:
                printf("Opcao invalida. Por favor, tente novamente.\n");
                esperarEnter();
        }
    } while (opcao != 0); // repete ate o usuario escolher sair 

    // Libera toda a memoria alocada dinamicamente antes de encerrar o programa
    liberarArvore(&arvore); 
    liberarFila(fila);
    liberarLista(historico);

    return 0;
}