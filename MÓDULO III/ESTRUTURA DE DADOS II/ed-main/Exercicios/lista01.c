/*
=====================================
  LISTA DE EXERCICIOS 01 - ARVORES
  Estruturas de Dados II - Modulo III
=====================================
*/

/*
PARTE 1 - QUESTOES CONCEITUAIS

01) c
02) b
03) c
04) c
05) b
06) a
07) d 
08) a 

09) Uma arvore em estruturas de dados e uma estrutura hierarquica nao-linear composta por
    nos conectados por arestas. Ela possui um no principal chamado raiz, e cada no pode
    ter zero ou mais nos filhos. A arvore e amplamente usada para representar hierarquias,
    como diretorios de arquivos, estruturas de menus e muito mais.

10) - No raiz: e o no que esta no topo da arvore, ou seja, nao possui pai. Toda arvore
       possui apenas um no raiz.
    - No folha: e o no que nao possui filhos, ficando nas extremidades da arvore.
    - No interno: e qualquer no que possui pelo menos um filho e que nao e a raiz.

11) Ancestral: um no A e ancestral de um no B se existe um caminho descendo de A ate B.
    Descendente: um no B e descendente de A se A e ancestral de B. Ou seja, sao os nos
    que estao abaixo de um determinado no na hierarquia.

12) A profundidade de um no e a distancia (numero de arestas) entre a raiz e esse no.
    A raiz possui profundidade 0, seus filhos profundidade 1, e assim por diante.

13) - Grau de um no: quantidade de filhos diretos que aquele no possui.
    - Grau de uma arvore: e o maior grau encontrado entre todos os nos da arvore.

14) As arvores sao fundamentais para sistemas computacionais modernos pois permitem
    organizar dados de forma hierarquica e eficiente. Sao usadas em sistemas de arquivos,
    bancos de dados (B-Trees), compiladores (arvores de sintaxe), algoritmos de busca,
    redes de computadores e inteligencia artificial. Sua principal vantagem e reduzir
    drasticamente o numero de comparacoes necessarias em buscas e ordenacoes.

15) Arvore desenhada com comentario:

                   A          <- raiz (nivel 0)
                 / | \
                B  C  D       <- nos internos (nivel 1)
               /|     |\
              E  F    G  H    <- folhas (nivel 2), exceto onde ha filhos
             /
            I                 <- folha (nivel 3)

    - Folhas: E (com filho I tornando-a interna), I, F, G, H, C, D sem filhos = C, F, G, H, I
    - Altura da arvore: 3 (caminho A -> B -> E -> I)
    - Grau da arvore: 3 (no A possui 3 filhos)
*/

#include <stdio.h>
#include <stdlib.h>

/* ============================================================
   ESTRUTURA DE NO PARA ARVORE GENERICA (Exercicio 16)
   Cada no armazena um valor e pode ter varios filhos
   usando lista encadeada de filhos.
   ============================================================ */
typedef struct No {
    int valor;
    struct No *primeiroFilho;  /* primeiro filho */
    struct No *proximoIrmao;   /* proximo irmao (lista de irmaos) */
} No;

/* ============================================================
   17) Inicializa arvore vazia - retorna NULL
   ============================================================ */
No* inicializarArvore() {
    return NULL;
}

/* ============================================================
   Cria um novo no com o valor informado
   ============================================================ */
No* criarNo(int valor) {
    No *novo = (No*) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Eroo: falha ao alocar memoria!\n");
        exit(1);
    }
    novo->valor = valor;
    novo->primeiroFilho = NULL;
    novo->proximoIrmao  = NULL;
    return novo;
}

/* ============================================================
   18) Insere um filho em um no pai
   ============================================================ */
void inserirFilho(No *pai, int valorFilho) {
    if (pai == NULL) {
        printf("Erro: no pai invalido!\n");
        return;
    }
    No *novoFilho = criarNo(valorFilho);

    /* se nao tem filhos ainda, torna-se o primeiro filho */
    if (pai->primeiroFilho == NULL) {
        pai->primeiroFilho = novoFilho;
    } else {
        /* percorre a lista de irmaos ate o ultimo */
        No *atual = pai->primeiroFilho;
        while (atual->proximoIrmao != NULL) {
            atual = atual->proximoIrmao;
        }
        atual->proximoIrmao = novoFilho;
    }
}

/* ============================================================
   19) Conta quantos nos existem na arvore (recursivo)
   ============================================================ */
int contarNos(No *raiz) {
    if (raiz == NULL) return 0;

    int contagem = 1; /* conta o proprio no */
    No *filho = raiz->primeiroFilho;
    while (filho != NULL) {
        contagem += contarNos(filho);
        filho = filho->proximoIrmao;
    }
    return contagem;
}

/* ============================================================
   20) Calcula a altura da arvore (recursivo)
   ============================================================ */
int calcularAltura(No *raiz) {
    if (raiz == NULL) return -1;
    if (raiz->primeiroFilho == NULL) return 0; /* folha tem altura 0 */

    int maiorAltura = -1;
    No *filho = raiz->primeiroFilho;
    while (filho != NULL) {
        int h = calcularAltura(filho);
        if (h > maiorAltura) maiorAltura = h;
        filho = filho->proximoIrmao;
    }
    return maiorAltura + 1;
}

/* ============================================================
   21) Conta quantas folhas existem na arvore
   ============================================================ */
int contarFolhas(No *raiz) {
    if (raiz == NULL) return 0;
    if (raiz->primeiroFilho == NULL) return 1; /* e uma folha */

    int folhas = 0;
    No *filho = raiz->primeiroFilho;
    while (filho != NULL) {
        folhas += contarFolhas(filho);
        filho = filho->proximoIrmao;
    }
    return folhas;
}

/* ============================================================
   22) Verifica se um valor existe na arvore
   ============================================================ */
int buscarValor(No *raiz, int valor) {
    if (raiz == NULL) return 0;
    if (raiz->valor == valor) return 1;

    No *filho = raiz->primeiroFilho;
    while (filho != NULL) {
        if (buscarValor(filho, valor)) return 1;
        filho = filho->proximoIrmao;
    }
    return 0;
}

/* ============================================================
   23) Imprime nos por nivel (BFS - usando fila auxiliar)
   ============================================================ */
/* fila simples para o BFS */
#define TAM_FILA 100

void imprimirPorNivel(No *raiz) {
    if (raiz == NULL) {
        printf("Arvore vazia!\n");
        return;
    }

    No *fila[TAM_FILA];
    int inicio = 0, fim = 0;
    fila[fim++] = raiz;

    int nivel = 0;
    printf("Nivel %d: ", nivel);

    /* usamos NULL como marcador de fim de nivel */
    fila[fim++] = NULL;

    while (inicio < fim) {
        No *atual = fila[inicio++];

        if (atual == NULL) {
            /* fim do nivel atual */
            if (inicio < fim) {
                nivel++;
                printf("\nNivel %d: ", nivel);
                fila[fim++] = NULL; /* marca proximo nivel */
            }
            continue;
        }

        printf("%d ", atual->valor);

        No *filho = atual->primeiroFilho;
        while (filho != NULL) {
            fila[fim++] = filho;
            filho = filho->proximoIrmao;
        }
    }
    printf("\n");
}

/* ============================================================
   24) Por que recursao e muito utilizada em arvores?
       (Resposta nos comentarios)

   A recursao e muito utilizada em arvores pois a propria estrutura
   de arvore e recursiva por natureza: cada subarvore e tambem uma arvore.
   Isso torna as solucoes recursivas naturais e elegantes, pois o mesmo
   algoritmo se aplica ao no atual e a todos os seus filhos, sem
   necessidade de controle manual de pilhas ou indices.

   ============================================================ */

/* ============================================================
   25) Libera toda a arvore da memoria
   ============================================================ */
void liberarArvore(No *raiz) {
    if (raiz == NULL) return;

    No *filho = raiz->primeiroFilho;
    while (filho != NULL) {
        No *proximo = filho->proximoIrmao;
        liberarArvore(filho);
        filho = proximo;
    }
    free(raiz);
}

/* ============================================================
   MAIN - demonstracao de todas as funcoes
   ============================================================ */
int main(void) {

    /*
         Arvore construida:
                1
              / | \
             2  3  4
            /|     |
           5  6    7
    */

    No *raiz = criarNo(1);
    inserirFilho(raiz, 2);
    inserirFilho(raiz, 3);
    inserirFilho(raiz, 4);

    No *no2 = raiz->primeiroFilho;          /* no 2 */
    inserirFilho(no2, 5);
    inserirFilho(no2, 6);

    No *no4 = no2->proximoIrmao->proximoIrmao; /* no 4 */
    inserirFilho(no4, 7);

    printf("=== Lista 01 - Arvores Genericas ===\n\n");

    printf("Total de nos: %d\n", contarNos(raiz));
    printf("Altura da arvore: %d\n", calcularAltura(raiz));
    printf("Total de folhas: %d\n", contarFolhas(raiz));

    int busca = 6;
    printf("Buscar valor %d: %s\n", busca,
           buscarValor(raiz, busca) ? "encontrado" : "nao encontrado");

    busca = 99;
    printf("Buscar valor %d: %s\n", busca,
           buscarValor(raiz, busca) ? "encontrado" : "nao encontrado");

    printf("\nImpressao por nivel:\n");
    imprimirPorNivel(raiz);

    liberarArvore(raiz);
    raiz = NULL;

    printf("\nMemoria liberada com suceso.\n");

    return 0;
}