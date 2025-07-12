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
    fgets(diploma->nome, 100,stdin);
    fgets(diploma->curso, 50, stdin);
    fgets(diploma->data_conclusao, 11, stdin);
    fgets(diploma->prazo, 11, stdin);

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

void listar_fila(Fila *fila){
    if(fila->base == NULL){
        printf("Não há diplomas a serem exibidos.");
        return;
    }

    Diploma *aux = fila->topo;
    printf("Diplomas:\n");
    while(aux != NULL){
        printf("ID:%d | Nome: %s | Curso: %s | Data de conclusão: %s | Prazo para retirada: %s", aux->id, aux->nome, aux->curso, aux->data_conclusao, aux->prazo);
        aux = aux->prox;
    }
}