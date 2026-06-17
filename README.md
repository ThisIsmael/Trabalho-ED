# Sistema de Gerenciamento de Biblioteca

Equipe: Ismael Sousa, Letícia Carneiro, Marina Carvalho  
Estruturas de Dados  
Universidade Estadual do Ceará (UECE)  
Professor: Bonfim Amaro

## Descrição do Sistema

O Sistema de Gerenciamento de Biblioteca foi desenvolvido em linguagem C com o objetivo de aplicar conceitos de Estruturas de Dados por meio da implementação de um sistema capaz de gerenciar livros, empréstimos e reservas.

## Funcionalidades

- Cadastro de livros;
- Busca de livros por código;
- Listagem de livros em ordem crescente;
- Listagem em pré-ordem;
- Listagem em pós-ordem;
- Empréstimo de livros;
- Devolução de livros;
- Controle de reservas;
- Exibição da fila de reservas;
- Histórico de empréstimos;
- Contagem de livros cadastrados;
- Cálculo da altura da árvore;
- Remoção de livros;
- Busca de livros por título ou autor.

## Estruturas de Dados Utilizadas

| Estrutura | Finalidade |
|------------|------------|
| Árvore Binária de Busca | Armazenar e organizar os livros cadastrados pelo código identificador |
| Fila Dinâmica | Gerenciar reservas de livros indisponíveis |
| Lista Encadeada | Armazenar o histórico de empréstimos realizados pelos usuários |
| Tipos Abstratos de Dados | Organizar as entidades do sistema |

## Compilação

No terminal, acesse a pasta do projeto e execute:

```bash
gcc src/*.c -o biblioteca
```

ou

```bash
gcc src/main.c src/livro.c src/arvore.c src/fila.c src/lista.c -o biblioteca
```

Após a compilação, execute:

### Linux/macOS

```bash
./biblioteca
```

### Windows

```bash
.\biblioteca.exe
```

## Exemplo de Uso

### Menu
```text
Bem-vindo a Biblioteca!
1.  Cadastrar Livro
2.  Buscar Livro por codigo
3.  Listar Livros em ordem crescente
4.  Listar Livros em pre-ordem
5.  Listar Livros em pos-ordem
6.  Emprestar Livro
7.  Devolver Livro
8.  Exibir fila de reservas
9.  Exibir historico de emprestimos
10. Exibir quantidade de livros cadastrados
11. Exibir altura da arvore
0.  Sair
Escolha uma opcao (apenas numeros):
```

### Cadastro de Livro

```text
Escolha uma opcao (apenas numeros): 1
Digite o codigo do livro (apenas numeros): 101
Digite o titulo do livro: Estrutura de Dados
Digite o autor do livro: Mark Allen Weiss
Digite o ano do livro: 2018
Digite a quantidade total de exemplares: 5
Livro cadastrado com sucesso!
```

### Busca de Livro

```text
Escolha uma opcao (apenas numeros): 2
Digite o codigo do livro: 101
Livro encontrado!
--------------------------------------------------
           Informacoes do Livro
--------------------------------------------------
Codigo: 101
Titulo: Estrutura de Dados
Autor: Mark Allen Weiss
Ano: 2018
Total: 5 exemplar(es)
Disponivel: 5 exemplar(es)
--------------------------------------------------
```

### Empréstimo

```text
Escolha uma opcao (apenas numeros): 6
Digite o nome do usuario: Bonfim
Digite o codigo do livro que deseja emprestar: 101
Livro emprestado com sucesso!
```

### Reserva

```text
Escolha uma opcao (apenas numeros): 6
Digite o nome do usuario: Allen
Digite o codigo do livro que deseja emprestar: 101
Nenhum exemplar disponivel.
Deseja entrar na fila de reservas?
1. Sim
2. Nao
Escolha uma opcao: 1
Usuario inserido na fila de reservas!
```

### Histórico

```text
===== HISTÓRICO DE EMPRÉSTIMOS =====
Usuário: Bonfim
Codigo do livro: 101
Titulo do livro: Estrutura de Dados
```

## Funcionalidades Implementadas

### TAD Livro

- Criação de livros;
- Exibição de informações;
- Controle de quantidade disponível;
- Empréstimo e devolução de exemplares.

### Árvore Binária de Busca

- Inserção de livros;
- Busca por código;
- Percursos em ordem, pré-ordem e pós-ordem;
- Contagem de livros;
- Cálculo da altura da árvore.

### Fila de Reservas

- Inserção de reservas;
- Remoção de reservas;
- Exibição da fila;
- Controle FIFO.

### Lista de Histórico

- Registro de empréstimos;
- Exibição do histórico;
- Inserção eficiente no início da lista.

## Limitações Conhecidas

- Os dados são armazenados apenas em memória.
- As informações são perdidas ao encerrar o programa.
- Não existe persistência em arquivos ou banco de dados.
- O sistema funciona via terminal.
