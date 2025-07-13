#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct diploma{
    int id;
    char nome[100];
    char curso[50];
    char data_conclusao[11];
    char prazo[11];
    struct diploma *prox;
}Diploma;

typedef struct fila{
    Diploma *topo;
    Diploma *base;
}Fila;

typedef struct pilha{
    Diploma *topo;
}Pilha;

Diploma *criar(int id){
    Diploma *diploma = (Diploma *)malloc(sizeof(Diploma));
    diploma->prox = NULL;
    diploma->id = id;

    printf("Insira os dados para a criação:\n");

    printf("Nome do aluno: ");
    fgets(diploma->nome, 100, stdin);
    diploma->nome[strcspn(diploma->nome, "\n")] = 0;

    printf("Curso: ");
    fgets(diploma->curso, 50, stdin);
    diploma->curso[strcspn(diploma->curso, "\n")] = 0;

    printf("Data de conclusão (DD/MM/AAAA): ");
    fgets(diploma->data_conclusao, 11, stdin);
    diploma->data_conclusao[strcspn(diploma->data_conclusao, "\n")] = 0;

    printf("Prazo limite para retirada (DD/MM/AAAA): ");
    fgets(diploma->prazo, 11, stdin);
    diploma->prazo[strcspn(diploma->prazo, "\n")] = 0;

    printf("Diploma adicionado à fila!\n");
    return diploma;
}

void enfileirar(Diploma *diploma, Fila *fila){
    if(fila->base == NULL){
        fila->base = diploma;
        fila->topo = diploma;
    }
    else{
        fila->base->prox = diploma;
        fila->base = diploma;
    }
}

Diploma* desenfileirar(Fila* fila) {
    if (fila->topo == NULL) {
        printf("Fila vazia!\n");
        return NULL;
    }
    Diploma *temp = fila->topo;
    fila->topo = fila->topo->prox;

    if (fila->topo == NULL) {
        fila->base = NULL;
    }
    temp->prox = NULL;
    return temp;
}

void listar_fila(Fila *fila){
    if(fila->base == NULL){
        printf("Não há diplomas a serem exibidos.");
        return;
    }

    Diploma *aux = fila->topo;
    printf("=== Diplomas na Fila (Prontos para retirada) ===\n");
    while(aux != NULL){
        printf("ID:%d | Nome: %s | Curso: %s | Data de conclusão: %s | Prazo para retirada: %s", aux->id, aux->nome, aux->curso, aux->data_conclusao, aux->prazo);
        aux = aux->prox;
    }
}

void empilhar(Pilha *pilha, Diploma *diploma) {
    diploma->prox = pilha->topo;
    pilha->topo = diploma;
}

Diploma *desempilhar(Pilha *pilha) {
    if (pilha->topo == NULL) {
        printf("Pilha vazia!\n");
        return NULL;
    }
    Diploma *temp = pilha->topo;
    pilha->topo = pilha->topo->prox;
    temp->prox = NULL;
    return temp;
}

void listar_pilha(Pilha *pilha) {
    Diploma* aux = pilha->topo;
    printf("=== Diplomas na Pilha (Separados para entrega) ===\n");
    while(aux != NULL) {
       printf("ID: %d | Nome: %s | Curso: %s\n", aux->id, aux->nome, aux->curso);
       aux = aux->prox; 
    }
}

int menu() {
    int opcao;
    printf("\n--- Menu ---\n");
    printf("1. Cadastrar diploma (enfileirar)\n");
    printf("2. Mostrar fila de diplomas\n");
    printf("3. Separar diploma para entrega (desenfileirar e empilhar)\n");
    printf("4. Mostrar pilha de diplomas separados\n");
    printf("5. Entregar diploma ao aluno (desempilhar)\n");
    printf("0. Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    getchar();
    return opcao;
}

int main() {
    Fila fila_diplomas = {NULL, NULL};
    Pilha pilha_diplomas = {NULL};

    int opcao;
    int id = 0;
    do { 
        opcao = menu();

        switch(opcao) {
            case 0:
                printf("Saindo....\n");
                break;
            case 1:
                id++;
                Diploma *novo = criar(id);
                enfileirar(novo, &fila_diplomas);
                break;
            case 2:
                listar_fila(&fila_diplomas);
                break;
            case 3:
                Diploma *pronto = desenfileirar(&fila_diplomas);
                if (pronto != NULL) {
                    empilhar(&pilha_diplomas, pronto);
                    printf("Diploma separado para entrega (movido para a pilha na mesa).\n");
                }
                break;
            case 4:
                listar_pilha(&pilha_diplomas);
                break;
            case 5:
                Diploma *entregue = desempilhar(&pilha_diplomas);
                if (entregue != NULL) {
                    printf("Diploma entregue ao aluno: %s\n", entregue->nome);
                    free(entregue);
                }
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (opcao != 0);

    while(fila_diplomas.topo != NULL) {
        Diploma *temp = desenfileirar(&fila_diplomas);
        free(temp);
    }
    while(pilha_diplomas.topo != NULL) {
        Diploma *temp = desempilhar(&pilha_diplomas);
        free(temp);
    }

    return 0;
}