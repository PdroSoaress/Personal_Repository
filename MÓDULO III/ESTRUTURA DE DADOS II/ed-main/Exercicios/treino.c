#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int dado;
    struct No* esq;
    struct No* dir;
} No;

No* criarNo(No* raiz, valor){
    No *novo = (No*) malloc(sizeof(No));
    novo->dado = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;   
}



No* inserir(No* raiz, int valor){
    if (raiz == NULL) return criarNo(valor);
    if (valor<raiz){
        raiz->esq = return inserir(raiz->esq, valor);
    }
    else if(valor>raiz){
        raiz->dir = return inserir(raiz->dir, valor);
    }
    return raiz;
}

void EmOrdem(No* raiz){
    if (raiz == NULL) return;
    EmOrdem(raiz->esq);
    printf("%d", raiz->valor);
    EmOrdem(raiz->dir);
}
void Preordem(No* raiz){
    if (raiz == NULL) return;
    printf("%d", raiz->valor);
    Preordem(raiz->esq);
    Preordem(raiz->dir);
}
void PosOrdem(No* raiz){
    if (raiz==NULL) return;
    PosOrdem(raiz->esq);
    PosOrdem(raiz->dir);
    printf("%d", raiz->valor);
}
No* buscar(No *raiz, int valor){
    if (raiz == NULL) return NULL;
    if (valor == raiz->valor) return raiz;
    else if (valor < raiz->valor) buscar(raiz->esq, valor);
    else if (valor > raiz->valor) buscar (raiz->dir, valor);
}