#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../headers/arvore.h"
#include "../headers/livro.h"

/* ==========================================================================
   Funções auxiliares recursivas
   ========================================================================== */

static NodeArvore* inserir_no_abbl(NodeArvore* no, Livro* livro) {
    if (no == NULL) {
        NodeArvore* novo_no = (NodeArvore*)malloc(sizeof(NodeArvore));
        if (novo_no != NULL) {
            novo_no->livro = livro;
            novo_no->esquerdo = NULL;
            novo_no->direito = NULL;
        }
        return novo_no;
    }
    
    if (livro->codigo < no->livro->codigo) {
        no->esquerdo = inserir_no_abbl(no->esquerdo, livro);
    } else if (livro->codigo > no->livro->codigo) {
        no->direito = inserir_no_abbl(no->direito, livro);
    }
    
    return no;
}

static NodeArvore* remover_no_abbl(NodeArvore* no, int codigo) {
    if (no == NULL) {
        return NULL;
    }

    if (codigo < no->livro->codigo) {
        no->esquerdo = remover_no_abbl(no->esquerdo, codigo);
    } else if (codigo > no->livro->codigo) {
        no->direito = remover_no_abbl(no->direito, codigo);
    } else {
        if (no->esquerdo == NULL) {
            NodeArvore* temp = no->direito;
            if (no->livro != NULL) free(no->livro);
            free(no);
            return temp;
        } else if (no->direito == NULL) {
            NodeArvore* temp = no->esquerdo;
            if (no->livro != NULL) free(no->livro);
            free(no);
            return temp;
        }

        NodeArvore* pai_sucessor = no;
        NodeArvore* sucessor = no->direito;
        while (sucessor->esquerdo != NULL) {
            pai_sucessor = sucessor;
            sucessor = sucessor->esquerdo;
        }

        if (no->livro != NULL) free(no->livro);
        no->livro = sucessor->livro;

        if (pai_sucessor == no) {
            pai_sucessor->direito = sucessor->direito;
        } else {
            pai_sucessor->esquerdo = sucessor->direito;
        }
        
        free(sucessor);
    }
    
    return no;
}

static void imprimir_livro(Livro* livro) {
    if (livro != NULL) {
        printf("Codigo: %d | Titulo: %s | Autor: %s | Ano: %d\n", 
               livro->codigo, livro->titulo, livro->autor, livro->ano);
    }
}

static void em_ordem_abbl(NodeArvore* no) {
    if (no != NULL) {
        em_ordem_abbl(no->esquerdo);
        imprimir_livro(no->livro);
        em_ordem_abbl(no->direito);
    }
}

static void pre_ordem_abbl(NodeArvore* no) {
    if (no != NULL) {
        imprimir_livro(no->livro);
        pre_ordem_abbl(no->esquerdo);
        pre_ordem_abbl(no->direito);
    }
}

static void pos_ordem_abbl(NodeArvore* no) {
    if (no != NULL) {
        pos_ordem_abbl(no->esquerdo);
        pos_ordem_abbl(no->direito);
        imprimir_livro(no->livro);
    }
}

static int contar_nos(NodeArvore* no) {
    if (no == NULL) return 0;
    return 1 + contar_nos(no->esquerdo) + contar_nos(no->direito);
}

static int altura_no(NodeArvore* no) {
    if (no == NULL) return -1;
    int alt_esq = altura_no(no->esquerdo);
    int alt_dir = altura_no(no->direito);
    return (alt_esq > alt_dir ? alt_esq : alt_dir) + 1;
}

static int contem_substring_ignorando_caso(const char* texto, const char* sub) {
    if (!*sub) return 1;
    char txt_lower[200];
    char sub_lower[200];
    
    int i = 0;
    while (texto[i] && i < 199) { txt_lower[i] = tolower((unsigned char)texto[i]); i++; }
    txt_lower[i] = '\0';
    
    i = 0;
    while (sub[i] && i < 199) { sub_lower[i] = tolower((unsigned char)sub[i]); i++; }
    sub_lower[i] = '\0';
    
    return strstr(txt_lower, sub_lower) != NULL;
}

static void buscar_por_titulo_autor_abbl(NodeArvore* no, const char* termo, int* encontrou) {
    if (no != NULL) {
        buscar_por_titulo_autor_abbl(no->esquerdo, termo, encontrou);
        
        if (contem_substring_ignorando_caso(no->livro->titulo, termo) || 
            contem_substring_ignorando_caso(no->livro->autor, termo)) {
            imprimir_livro(no->livro);
            *encontrou = 1;
        }
        
        buscar_por_titulo_autor_abbl(no->direito, termo, encontrou);
    }
}

/* ==========================================================================
   Implementação das funções principais do TAD
   ========================================================================== */

void inserirLivroArvore(Arvore* arvore, Livro* livro) {
    if (arvore == NULL || livro == NULL) return;
    arvore->raiz = inserir_no_abbl(arvore->raiz, livro);
}

void removerLivroArvore(Arvore* arvore, int codigo) {
    if (arvore == NULL) return;
    arvore->raiz = remover_no_abbl(arvore->raiz, codigo);
}

Livro* buscarLivroArvore(Arvore* arvore, int codigo) {
    if (arvore == NULL) return NULL;
    
    NodeArvore* atual = arvore->raiz;
    while (atual != NULL) {
        if (codigo == atual->livro->codigo) {
            return atual->livro;
        } else if (codigo < atual->livro->codigo) {
            atual = atual->esquerdo;
        } else {
            atual = atual->direito;
        }
    }
    return NULL;
}

void buscarLivrosPorTituloOuAutor(Arvore* arvore, const char* termo) {
    if (arvore == NULL || termo == NULL) return;
    int encontrou = 0;
    printf("Resultados da busca por '%s':\n", termo);
    buscar_por_titulo_autor_abbl(arvore->raiz, termo, &encontrou);
    if (!encontrou) {
        printf("Nenhum livro encontrado com esse termo.\n");
    }
}

void listarLivrosEmOrdem(Arvore* arvore) {
    if (arvore == NULL) return;
    em_ordem_abbl(arvore->raiz);
}

void listarLivrosPreOrdem(Arvore* arvore) {
    if (arvore == NULL) return;
    pre_ordem_abbl(arvore->raiz);
}

void listarLivrosPosOrdem(Arvore* arvore) {
    if (arvore == NULL) return;
    pos_ordem_abbl(arvore->raiz);
}

int contarLivros(Arvore* arvore) {
    if (arvore == NULL) return 0;
    return contar_nos(arvore->raiz);
}

int calcularAlturaArvore(Arvore* arvore) {
    if (arvore == NULL) return -1;
    return altura_no(arvore->raiz);
}

static void liberar_nos_abbl(NodeArvore* no) {
    if (no != NULL) {
        liberar_nos_abbl(no->esquerdo);
        liberar_nos_abbl(no->direito);
        if (no->livro != NULL) free(no->livro);
        free(no);
    }
}

void liberarArvore(Arvore* arvore) {
    if (arvore != NULL) {
        liberar_nos_abbl(arvore->raiz);
        arvore->raiz = NULL;
    }
}