/*
=============================================
  LISTA DE EXERCICIOS 02 - ARVORES BINARIAS
*/

/*

01) b - Cada no pode possuir no maximo dois filhoss
02) c - Cada no pode ter filho esquerdo e direito
03) c - Pré-ordem
04) b - Em ordem  
05) a - Pós-ordem  
06) b - Possui todos os niveis completos, excet possivelmente o ultimo

07) Arvore binaria cheia e a arvore onde todos os nos internos tem dois filhos
    e no ultimo nivel ha apenas folhas, sem filhos.
    Arvore completa e uma arvore onde os niveis internos estao preenchidos, menos
    o ultimo, ele pode ou nao estar preenchido, mas suas folhas devem estar
    preenchidas da esquerda pra direita.

08) Pre-ordem: Faz o percurso Pai-Esquerda-Direita
    Em ordem: Faz o percurso do menor ao maior numero, que no caso seria:
              Esquerda, Pai, Direito.
    Pos-ordem: Faz o percurso: Esquerda-Direita-Pai

09) Em situacoes onde ha um sistema com milhares e milhares de registros.
    Pois a cada vez que e feita uma comparacao, metade das possibilidades
    sao descartadas.

10) Considerando a arvore abaixo:

               5
             /   \
            4     7
           /     / \
          2     6   8
         / \       / \
        1   3     9   10

    Pre-Ordem:  5, 4, 2, 1, 3, 7, 6, 8, 9, 10
    Em ordem:   1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    Pos-Ordem:  1, 3, 2, 4, 6, 9, 10, 8, 7, 5
*/

#include <stdio.h>
#include <stdlib.h>

/* ============================================================
   36) Estrutura de um no de arvore binaria
   ============================================================ */
typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

No* criarNo(int valor) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Eroo: falha ao alocar memoriia!\n");
        exit(1);
    }
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

/* ============================================================
   37) Insere nos manualmente (sem regra de BST, apenas
       preenche da esquerda para direita usando fila auxiliar)
   ============================================================ */
No* inserirManual(No *raiz, int valor) {
    No *novo = criarNo(valor);
    if (raiz == NULL) return novo;

    /* BFS para encontrar o primeiro espaco vazio */
    No *fila[100];
    int inicio = 0, fim = 0;
    fila[fim++] = raiz;

    while (inicio < fim) {
        No *atual = fila[inicio++];
        if (atual->esq == NULL) {
            atual->esq = novo;
            return raiz;
        } else {
            fila[fim++] = atual->esq;
        }
        if (atual->dir == NULL) {
            atual->dir = novo;
            return raiz;
        } else {
            fila[fim++] = atual->dir;
        }
    }
    return raiz;
}

/* ============================================================
   38) Percurso Pre-ordem: Raiz -> Esquerda -> Direita
   ============================================================ */
void preOrdem(No *raiz) {
    if (raiz == NULL) return;
    printf("%d ", raiz->valor);
    preOrdem(raiz->esq);
    preOrdem(raiz->dir);
}

/* ============================================================
   39) Percurso Em ordem: Esquerda -> Raiz -> Direita
   ============================================================ */
void emOrdem(No *raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esq);
    printf("%d ", raiz->valor);
    emOrdem(raiz->dir);
}

/* ============================================================
   40) Percurso Pos-ordem: Esquerda -> Direita -> Raiz
   ============================================================ */
void posOrdem(No *raiz) {
    if (raiz == NULL) return;
    posOrdem(raiz->esq);
    posOrdem(raiz->dir);
    printf("%d ", raiz->valor);
}

/* ============================================================
   41) Conta o numero de nos da arvore binaria
   ============================================================ */
int contarNos(No *raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

/* ===================
   42) Calcula a altura da arvore binari */
int calcularAltura(No *raiz) {
    if (raiz == NULL) return -1;
    int altEsq = calcularAltura(raiz->esq);
    int altDir = calcularAltura(raiz->dir);
    return 1 + (altEsq > altDir ? altEsq : altDir);
}

/* 
   43) Conta quantos nos folhas existem
*/
int contarFolhas(No *raiz) {
    if (raiz == NULL) return 0;
    if (raiz->esq == NULL && raiz->dir == NULL) return 1;
    return contarFolhas(raiz->esq) + contarFolhas(raiz->dir);
}

/* 
   44) Espelha uma arvore binaria (inverte esq e dir)
  */
void espelharArvore(No *raiz) {
    if (raiz == NULL) return;

    /* troca os filhos */
    No *temp = raiz->esq;
    raiz->esq = raiz->dir;
    raiz->dir = temp;

    /* repete recursivamente */
    espelharArvore(raiz->esq);
    espelharArvore(raiz->dir);
}

/* ============================================================
   45) Verifica se duas arvores binarias sao iguais
   ============================================================ */
int arvoreSaoIguais(No *a, No *b) {
    if (a == NULL && b == NULL) return 1;
    if (a == NULL || b == NULL) return 0;
    if (a->valor != b->valor)   return 0;
    return arvoreSaoIguais(a->esq, b->esq) &&
           arvoreSaoIguais(a->dir, b->dir);
}

/* ============================================================
   Libera a arvore da memoria
   ============================================================ */
void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

/* ============================================================
   Copia uma arvore (auxiliar para demonstracao do exercicio 45)
   ============================================================ */
No* copiarArvore(No *raiz) {
    if (raiz == NULL) return NULL;
    No *novo = criarNo(raiz->valor);
    novo->esq = copiarArvore(raiz->esq);
    novo->dir = copiarArvore(raiz->dir);
    return novo;
}

/* ============================================================
   MAIN - demonstracao de todas as funcoes
   ============================================================ */
int main(void) {

    No *raiz = NULL;

    /* insere nos manualmente (nivel a nivel) */
    int valores[] = {5, 4, 7, 2, 6, 8, 1, 3, 9, 10};
    int n = sizeof(valores) / sizeof(valores[0]);
    for (int i = 0; i < n; i++) {
        raiz = inserirManual(raiz, valores[i]);
    }

    printf("=== Lista 02 - Arvores Binarias ===\n\n");

    printf("Pre-Ordem:  ");
    preOrdem(raiz);
    printf("\n");

    printf("Em Ordem:   ");
    emOrdem(raiz);
    printf("\n");

    printf("Pos-Ordem:  ");
    posOrdem(raiz);
    printf("\n");

    printf("Total de nos: %d\n", contarNos(raiz));
    printf("Altura da arvore: %d\n", calcularAltura(raiz));
    printf("Total de folhas: %d\n", contarFolhas(raiz));

    /* Exercicio 44 - espelhar */
    printf("\nApos espelhar a arvore:\n");
    espelharArvore(raiz);
    printf("Em Ordem espelhada: ");
    emOrdem(raiz);
    printf("\n");

    /* desfaz espelhamento para demonstrar exercicio 45 */
    espelharArvore(raiz);

    /* Exercicio 45 - comparar duas arvores */
    No *copia = copiarArvore(raiz);
    printf("\nArvore igual a sua copia: %s\n",
           arvoreSaoIguais(raiz, copia) ? "sim" : "nao");

    /* modifica a copia e compara novamente */
    copia->valor = 999;
    printf("Arvore igual apos modificar copia: %s\n",
           arvoreSaoIguais(raiz, copia) ? "sim" : "nao");

    liberarArvore(raiz);
    liberarArvore(copia);
    raiz = NULL;

    printf("\nMemoria liberada com sucsso.\n");

    return 0;
}
