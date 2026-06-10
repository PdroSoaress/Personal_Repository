/*
==========================================================
  LISTA DE EXERCICIOS 03 - ARVORES BINARIAS DE BUSCA (ABB)
  Estruturas de Dados II - Modulo III
==========================================================
*/

/*
QUESTOES CONCEITUAIS

01) c
02) c
03) b
04) b

05)  ao inserir em uma ABB, compare o valor com o nó atual; se for menor, 
vá para a subárvore esquerda; se for maior, para a direita; repita até encontrar 
um ponteiro NULL e insira o novo nó.

06) A busca em uma ABB compara o valor procurado com o no atual. Se for igual, foi
    encontrado. Se for menor, continua buscando na subarvore esquerda. se for maior,
    na direita. Isso garante que a cada passo metade da arvore e descartada.

07)
    - Remocao de folha(sem filhos): basta remover o no e apontar o pai para NULL.
    - Remocao de no com um filho(direita ou esquerda): o no e removido e o seu unico filho assume
      seu lugar, sendo apontado diretamente pelo pai.
    - Remocao de no com dois filhos: encontra-se o sucessor em ordem (menor
      no da subarvore direita), copia seu valor para o no a ser removido,
      e entao remove o sucessor (que tem no maximo um filho).

08) A principal vantagem da ABB e a busca eficiente. Como os dados ficam
    organizados (menores a esquerda, maiores a direita), e possivel descartar
    metade da arvore em cada comparacao, atingindo complexidade O(log n) em
    arvores balanceadas, contra O(n) em listas ou vetores nao ordenados.

09) O desbalanceamento ocorre quando os dados sao inseridos em ordem crescente
    ou decrescente, fazendo com que todos os nos fiquem apenas em um lado.
    Nesse caso a arvore degenera em uma lista encadeada e a busca passa a
    ser O(n), perdendo toda a eficiencia esperada.
*/

#include <stdio.h>
#include <stdlib.h>

/* ============================================================
   ESTRUTURA DO NO
   ============================================================ */
typedef struct No {
    int valor;
    struct No *esq;
    struct No *dir;
} No;

/* ============================================================
   Funcao auxiliar: cria novo no
   ============================================================ */
No* criarNo(int valor) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Eroo: falha ao alocar memoria!\n");
        exit(1);
    }
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

/* ============================================================
   10) Insercao em ABB usando recursao
   ============================================================ */
No* inserir(No *raiz, int valor) {
    if (raiz == NULL) return criarNo(valor);
    if (valor < raiz->valor)
        raiz->esq = inserir(raiz->esq, valor);
    else if (valor > raiz->valor)
        raiz->dir = inserir(raiz->dir, valor);
    return raiz;
}

/* ============================================================
   11) Busca em ABB
   ============================================================ */
No* buscar(No *raiz, int valor) {
    if (raiz == NULL) return NULL;
    if (valor == raiz->valor) return raiz;
    if (valor < raiz->valor) return buscar(raiz->esq, valor);
    return buscar(raiz->dir, valor);
}

/* ============================================================
   12) Percurso em ordem (retorna valores ordenados na ABB)
   ============================================================ */
void emOrdem(No *raiz) {
    if (raiz == NULL) return;
    emOrdem(raiz->esq);
    printf("%d ", raiz->valor);
    emOrdem(raiz->dir);
}

/* ============================================================
   16) Encontra o menor valor da ABB
   ============================================================ */
No* encontrarMin(No *raiz) {
    if (raiz == NULL) return NULL;
    while (raiz->esq != NULL) raiz = raiz->esq;
    return raiz;
}

/* ============================================================
   16) Encontra o maior valor da ABB
   ============================================================ */
No* encontrarMax(No *raiz) {
    if (raiz == NULL) return NULL;
    while (raiz->dir != NULL) raiz = raiz->dir;
    return raiz;
}

/* ============================================================
   13 + 14 + 15) Remocao completa (cobre os tres casos):
   - folha (13)
   - no com um filho (14)
   - no com dois filhos usando sucessor em ordem (15)
   ============================================================ */
No* remover(No *raiz, int valor) {
    if (raiz == NULL) return NULL;

    if (valor < raiz->valor) {
        raiz->esq = remover(raiz->esq, valor);
    } else if (valor > raiz->valor) {
        raiz->dir = remover(raiz->dir, valor);
    } else {
        /* caso 1: folha - nao tem filhos */
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            return NULL;
        }
        /* caso 2a: so tem filho direito */
        if (raiz->esq == NULL) {
            No *temp = raiz->dir;
            free(raiz);
            return temp;
        }
        /* caso 2b: so tem filho esquerdo */
        if (raiz->dir == NULL) {
            No *temp = raiz->esq;
            free(raiz);
            return temp;
        }
        /* caso 3: dois filhos - usa o sucessor em ordem (minimo da direita) */
        No *succ = encontrarMin(raiz->dir);
        raiz->valor = succ->valor;
        raiz->dir = remover(raiz->dir, succ->valor);
    }
    return raiz;
}

/* ============================================================
   17) Verifica se uma arvore e uma ABB valida
   ============================================================ */
int ehABBValida(No *raiz, int min, int max) {
    if (raiz == NULL) return 1;
    if (raiz->valor <= min || raiz->valor >= max) return 0;
    return ehABBValida(raiz->esq, min, raiz->valor) &&
           ehABBValida(raiz->dir, raiz->valor, max);
}

/* ============================================================
   18) Conta quantos niveis (altura + 1) existem na ABB
   ============================================================ */
int contarNiveis(No *raiz) {
    if (raiz == NULL) return 0;
    int esq = contarNiveis(raiz->esq);
    int dir = contarNiveis(raiz->dir);
    return 1 + (esq > dir ? esq : dir);
}

/* ============================================================
   Conta total de nos (auxiliar para o menu)
   ============================================================ */
int contarNos(No *raiz) {
    if (raiz == NULL) return 0;
    return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

/* ============================================================
   Libera toda a arvore da memoria
   ============================================================ */
void liberarArvore(No *raiz) {
    if (raiz == NULL) return;
    liberarArvore(raiz->esq);
    liberarArvore(raiz->dir);
    free(raiz);
}

/* ============================================================
   19) Programa completo com menu
   ============================================================ */
void exibirMenu() {
    printf("\n===== ABB - Menu =====\n");
    printf("1. Inserir\n");
    printf("2. Buscar\n");
    printf("3. Remover\n");
    printf("4. Imprimir em ordem\n");
    printf("5. Mostrar altura\n");
    printf("6. Encerrar\n");
    printf("Escolha uma opçao: ");
}

void executarMenu() {
    No *raiz = NULL;
    int opcao, valor;

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Valor para insereir: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                printf("Valor %d inseridoo com sucesso!\n", valor);
                break;

            case 2:
                printf("Valor para buscar: ");
                scanf("%d", &valor);
                No *encontrado = buscar(raiz, valor);
                if (encontrado)
                    printf("Valor %d encontardo na arvore.\n", valor);
                else
                    printf("Valor %d nao encontrado.\n", valor);
                break;

            case 3:
                printf("Valor para remover: ");
                scanf("%d", &valor);
                if (buscar(raiz, valor)) {
                    raiz = remover(raiz, valor);
                    printf("Valor %d removiddo.\n", valor);
                } else {
                    printf("Valor %d nao existe na arvore.\n", valor);
                }
                break;

            case 4:
                printf("Em ordem: ");
                if (raiz == NULL)
                    printf("(arvore vazia)");
                else
                    emOrdem(raiz);
                printf("\n");
                break;

            case 5:
                printf("Altura da ABB: %d\n", contarNiveis(raiz) - 1);
                break;

            case 6:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opçao invalida!\n");
        }
    } while (opcao != 6);

    liberarArvore(raiz);
}

/* ============================================================
   20) ABB sem recursao - insercao iterativa
   ============================================================ */
No* inserirIterativo(No *raiz, int valor) {
    No *novo = criarNo(valor);
    if (raiz == NULL) return novo;

    No *atual = raiz;
    No *pai = NULL;

    while (atual != NULL) {
        pai = atual;
        if (valor < atual->valor)
            atual = atual->esq;
        else if (valor > atual->valor)
            atual = atual->dir;
        else {
            /* valor duplicado, nao insere */
            free(novo);
            return raiz;
        }
    }

    if (valor < pai->valor)
        pai->esq = novo;
    else
        pai->dir = novo;

    return raiz;
}

/* ============================================================
   20) Busca iterativa (sem recursao)
   ============================================================ */
No* buscarIterativo(No *raiz, int valor) {
    while (raiz != NULL) {
        if (valor == raiz->valor) return raiz;
        if (valor < raiz->valor) raiz = raiz->esq;
        else raiz = raiz->dir;
    }
    return NULL;
}

/* ============================================================
   21) Arvore binaria com alocacao dinamica - ja implementada
       com malloc em criarNo(). Demonstracao adicional abaixo
       de realloc de um vetor de ponteiros para nos.
   ============================================================ */
typedef struct ArvoresDinamicas {
    No **arvores;
    int quantidade;
    int capacidade;
} ArvoresDinamicas;

ArvoresDinamicas* criarConjunto() {
    ArvoresDinamicas *conj = (ArvoresDinamicas*) malloc(sizeof(ArvoresDinamicas));
    conj->capacidade = 4;
    conj->quantidade = 0;
    conj->arvores = (No**) malloc(conj->capacidade * sizeof(No*));
    return conj;
}

void adicionarArvore(ArvoresDinamicas *conj, No *raiz) {
    if (conj->quantidade == conj->capacidade) {
        conj->capacidade *= 2;
        conj->arvores = (No**) realloc(conj->arvores,
                         conj->capacidade * sizeof(No*));
    }
    conj->arvores[conj->quantidade++] = raiz;
}

/* ============================================================
   22) Transforma uma arvore em espelho (inverte esq e dir)
   ============================================================ */
void espelharArvore(No *raiz) {
    if (raiz == NULL) return;
    No *temp = raiz->esq;
    raiz->esq = raiz->dir;
    raiz->dir = temp;
    espelharArvore(raiz->esq);
    espelharArvore(raiz->dir);
}

/* ============================================================
   23) Verifica se a arvore e balanceada
       (diferenca de altura entre subarvores <= 1 em cada no)
   ============================================================ */
int alturaBalanceada(No *raiz) {
    if (raiz == NULL) return 0;

    int altEsq = alturaBalanceada(raiz->esq);
    if (altEsq == -1) return -1;

    int altDir = alturaBalanceada(raiz->dir);
    if (altDir == -1) return -1;

    int diff = altEsq - altDir;
    if (diff < -1 || diff > 1) return -1;

    return 1 + (altEsq > altDir ? altEsq : altDir);
}

int ehBalanceada(No *raiz) {
    return alturaBalanceada(raiz) != -1;
}

/* ============================================================
   24) Pesquisa: AVL, Rubro-Negra e B-Tree

   AVL:
   E uma ABB auto-balanceada onde a diferenca de altura entre
   as subarvores esquerda e direita de qualquer no e no maximo 1.
   Apos cada insercao ou remocao, rotacoes sao feitas para manter
   esse balanceamento. Garante O(log n) em todas as operacoes.

   Arvore Rubro-Negra:
   E uma ABB auto-balanceada onde cada no recebe uma cor (vermelho
   ou preto). Um conjunto de regras sobre as cores garante que o
   caminho mais longo ate uma folha seja no maximo duas vezes o
   caminho mais curto. Usada internamente em diversas linguagens

   B-Tree:
   E uma arvore de busca generalizada onde cada no pode ter varios
   filhos (nao apenas dois). E muito usada em banco de dados e
   sistemas de arquivos pois e otimizada para leitura e escrita
   em disco, minimizando o numero de acessos. Cada no armazena
   multiplas chaves, e os filhos ficam entre as chaves.
   ============================================================ */

/* ============================================================
   MAIN - demonstracao das funcoes e menu interativo
   ============================================================ */
int main(void) {
    printf("=== Lista 03 - Arvores Binarias de Busca (ABB) ===\n\n");

    /* demonstracao basica */
    No *raiz = NULL;
    int valores[] = {50, 30, 70, 20, 40, 60, 80};
    int n = sizeof(valores) / sizeof(valores[0]);
    for (int i = 0; i < n; i++) {
        raiz = inserir(raiz, valores[i]);
    }

    printf("Em Ordem: ");
    emOrdem(raiz);
    printf("\n");

    No *min = encontrarMin(raiz);
    No *max = encontrarMax(raiz);
    printf("Menor valor: %d\n", min ? min->valor : -1);
    printf("Maior valor: %d\n", max ? max->valor : -1);
    printf("Niveis da ABB: %d\n", contarNiveis(raiz));
    printf("E uma ABB valida: %s\n",
           ehABBValida(raiz, -2147483648, 2147483647) ? "sim" : "nao");
    printf("E balanceada: %s\n", ehBalanceada(raiz) ? "sim" : "nao");

    /* teste busca iterativa */
    printf("Busca iterativa por 40: %s\n",
           buscarIterativo(raiz, 40) ? "encontrado" : "nao encontrado");
    printf("Busca iterativa por 99: %s\n",
           buscarIterativo(raiz, 99) ? "encontrado" : "nao encontrado");

    /* remocao dos tres casos */
    printf("\nRemovendo 20 (folha)...\n");
    raiz = remover(raiz, 20);
    printf("Em Ordem: ");
    emOrdem(raiz);
    printf("\n");

    printf("Removendo 30 (um filho)...\n");
    raiz = remover(raiz, 30);
    printf("Em Ordem: ");
    emOrdem(raiz);
    printf("\n");

    printf("Removendo 50 (dois filhos)...\n");
    raiz = remover(raiz, 50);
    printf("Em Ordem: ");
    emOrdem(raiz);
    printf("\n");

    /* teste espelhar */
    printf("\nApos espelhar:\n");
    espelharArvore(raiz);
    printf("Em Ordem espelhada: ");
    emOrdem(raiz);
    printf("\n");

    liberarArvore(raiz);
    raiz = NULL;

    /* demonstracao insercao iterativa */
    printf("\n--- Insercao iterativa (sem recursao) ---\n");
    No *raiz2 = NULL;
    for (int i = 0; i < n; i++) {
        raiz2 = inserirIterativo(raiz2, valores[i]);
    }
    printf("Em Ordem (iterativo): ");
    emOrdem(raiz2);
    printf("\n");
    liberarArvore(raiz2);

    printf("\n--- Menu interativo ---\n");
    executarMenu();

    return 0;
}