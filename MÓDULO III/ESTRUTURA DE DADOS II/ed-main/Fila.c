#include <stdio.h>
#include <stdlib.h>

// ============================
// ESTRUTURA DO NÓ
// ============================
typedef struct No {
    int valor;
    struct No *prox;
} No;

// ponteiro para o início da lista
No *head = NULL;

// ============================
// INSERIR (no início)
// ============================
void inserir() {
    No *novo = (No*) malloc(sizeof(No));

    if (novo == NULL) {
        printf("Erro de alocacao!\n");
        return;
    }

    printf("Digite o valor: ");
    scanf("%d", &novo->valor);

    novo->prox = head;
    head = novo;

    printf("Elemento inserido!\n");
}

// ============================
// REMOVER (por valor)
// ============================
void remover() {
    if (head == NULL) {
        printf("Lista vazia!\n");
        return;
    }
    No*anterior = NULL;
    No*atual = head;

    while (atual->prox!=NULL){
        anterior=atual;
        atual = atual->prox;
    }
    anterior->prox = NULL;

    free(atual);

    printf("Elemento removido!\n");
}

// ============================
// BUSCAR
// ============================
void buscar() {
    if (head == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    int valor, pos = 0;
    printf("Digite o valor a buscar: ");
    scanf("%d", &valor);

    No *atual = head;

    while (atual != NULL) {
        if (atual->valor == valor) {
            printf("Encontrado na posicao %d\n", pos);
            return;
        }
        atual = atual->prox;
        pos++;
    }

    printf("Nao encontrado!\n");
}

// ============================
// EXIBIR
// ============================
void exibir() {
    if (head == NULL) {
        printf("Lista vazia!\n");
        return;
    }

    No *atual = head;

    printf("\nLista:\n");

    while (atual != NULL) {
        printf("[Valor: %d | Endereco: %p | Prox: %p] -> ",
               atual->valor, atual, atual->prox);
        atual = atual->prox;
    }

    printf("NULL\n");
}

// ============================
// MENU
// ============================
void menu() {
    printf("\n===== LISTA ENCADEADA =====\n");
    printf("1 - Inserir Elemento\n");
    printf("2 - Remover Elemento\n");
    printf("3 - Buscar Elemento\n");
    printf("4 - Exibir Lista\n");
    printf("5 - Sair\n");
    printf("Opcao: ");
}

// ============================
// MAIN
// ============================
int main() {
    int opcao;

    do {
        menu();
        scanf("%d", &opcao);

        if (opcao == 1) inserir();
        else if (opcao == 2) remover();
        else if (opcao == 3) buscar();
        else if (opcao == 4) exibir();
        else if (opcao == 5) printf("Encerrando...\n");
        else printf("Opcao invalida!\n");

    } while (opcao != 5);

    return 0;
}